#ifndef ARABICA_XSLT_STYLESHEETCONSTANT_HPP
#define ARABICA_XSLT_STYLESHEETCONSTANT_HPP

#include <XML/XMLCharacterClasses.hpp>
#include <XPath/impl/xpath_namespace_context.hpp>
#include <memory>

#include "xslt_stylesheet_parser.hpp"
#include "xslt_compiled_stylesheet.hpp"
#include "xslt_compilation_context.hpp"
#include "handler/xslt_value_validation.hpp"
#include "handler/xslt_template_handler.hpp"
#include "handler/xslt_include_handler.hpp"
#include "handler/xslt_output_handler.hpp"
#include "handler/xslt_namespace_alias_handler.hpp"
#include "handler/xslt_key_handler.hpp"
#include "handler/xslt_foreign_element_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class StylesheetHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
public:
  typedef string_type stringT;
  typedef string_adaptor string_adaptorT;
  typedef SAX::Attributes<string_type, string_adaptor> AttributesT;
  typedef SAX::DefaultHandler<string_type, string_adaptor> DefaultHandlerT;
  typedef CompilationContext<string_type, string_adaptor> CompilationContextT;

  StylesheetHandler(CompilationContextT& context) :
    context_(context),
    top_(false)
  {
    context_.root(*this);
    includer_.context(context_, this);      
  } // StylesheetHandler

  virtual void startDocument()
  {
    top_ = true;
  } // startDocument

  virtual void startElement(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const AttributesT& atts)
  {
    if(top_)
    {
      top_ = false;
      if(namespaceURI == StylesheetConstant::NamespaceURI())
        startStylesheet(namespaceURI, localName, qName, atts);
      else
        startLREAsStylesheet(namespaceURI, localName, qName, atts);
      return;
    } // if(top_)

    if(namespaceURI == StylesheetConstant::NamespaceURI())
      startXSLTElement(namespaceURI, localName, qName, atts);
    else if(!namespaceURI.empty())
      startForeignElement(namespaceURI, localName, qName, atts);
    else
      oops(qName);
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData(ch, "xsl:stylesheet/xsl:transform");
  } // characters

  virtual void endDocument()
  {
    includer_.unwind_imports();
    context_.stylesheet().prepare();
  } // endDocument

private:
  void startStylesheet(const string_type& /* namespaceURI */,
                       const string_type& localName,
                       const string_type& qName,
                       const AttributesT& atts)
  {
    if(localName != "stylesheet" && localName != "transform")
      throw SAX::SAXException("Top-level element must be 'stylesheet' or 'transform'.");
    
    static const ValueRule rules[] = { { "version", true, 0, 0 },
                                       { "extension-element-prefixes", false, 0, 0 },
                                       { "exclude-result-prefixes", false, 0, 0 },
                                       { "id", false, 0, 0 },
                                       { 0, false, 0, 0 } };
    std::map<string_type, string_type> attributes = gatherAttributes(qName, atts, rules);
    if(attributes["version"] != StylesheetConstant::Version())
      throw SAX::SAXException("I'm only a poor version 1.0 XSLT Transformer.");
    if(!attributes["extension-element-prefixes"].empty())
      throw SAX::SAXException("Haven't implemented extension-element-prefixes yet");
  } // startStylesheet

  void startLREAsStylesheet(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const AttributesT& atts)
  {
    string_type version;
    for(int a = 0; a != atts.getLength(); ++a)
      if((StylesheetConstant::NamespaceURI() == atts.getURI(a)) &&
         ("version" == atts.getLocalName(a)))
      {
        version = atts.getValue(a);
        break;
      }

    if(version.empty())
      throw SAX::SAXException("The source file does not look like a stylesheet.");
    if(version != StylesheetConstant::Version())
      throw SAX::SAXException("I'm only a poor version 1.0 XSLT Transformer.");

    Template* lreStylesheet = new Template(context_.xpath_match("/"), "", "", "", context_.precedence());
    context_.push(lreStylesheet,
                  new LREStylesheetHandler<string_type, string_adaptor>(context_, lreStylesheet),
                  namespaceURI, 
                  localName, 
                  qName, 
                  atts);
  } // startLREAsStylesheet

  void startXSLTElement(const string_type& namespaceURI,
                        const string_type& localName,
                        const string_type& qName,
                        const AttributesT& atts)
  {
    if((localName == "import") || (localName == "include"))
    {
      include_stylesheet(namespaceURI, localName, qName, atts);
      return;
    } // if ...
    
    for(const ChildElement* c = allowedChildren; c->name != 0; ++c)
      if(c->name == localName)
      {
        context_.push(0,
                      c->createHandler(context_),
                      namespaceURI, 
                      localName, 
                      qName, 
                      atts);
        return;
      } // if ...

    oops(qName);
  } // startXSLTElement

  void startForeignElement(const string_type& namespaceURI,
                           const string_type& localName,
                           const string_type& qName,
                           const AttributesT& atts)
  {
    context_.push(0,
                  new ForeignElementHandler(context_),
                  namespaceURI,
                  localName,
                  qName,
                  atts);
  } // startForeignElement

  void include_stylesheet(const string_type& namespaceURI,
                          const string_type& localName,
                          const string_type& qName,
                          const AttributesT& atts)
  {
    includer_.start_include(namespaceURI, localName, qName, atts);
  } // include_stylesheet

  void oops(const string_type& qName) const
  {
    throw SAX::SAXException("xsl:stylesheet does not allow " + qName + " here.");  
  } // oops
  
  CompilationContextT& context_;
  DefaultHandlerT* child_;
  IncludeHandler includer_;
  bool top_;

  static const ChildElement allowedChildren[];
}; // class StylesheetHandler

template<class string_type, class string_adaptor>
const ChildElement StylesheetHandler<string_type, string_adaptor>::allowedChildren[] =
  {
    { "attribute-set", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    { "decimal-format", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    //"import"
    //"include"
    { "key", CreateHandler<KeyHandler>},
    { "namespace-alias", CreateHandler<NamespaceAliasHandler>},
    { "output", CreateHandler<OutputHandler>},
    { "param", CreateHandler<TopLevelVariableHandler<Param> >},
    { "preserve-space", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    { "strip-space", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    { "template", CreateHandler<TemplateHandler> },
    { "variable", CreateHandler<TopLevelVariableHandler<Variable> > },
    { 0, 0 }
  }; // StylesheetHandler::allowedChildren

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StylesheetCompiler 
{
public:
  typedef string_type string_typeT;
  typedef string_adaptor string_adaptorT;
  typedef SAX::InputSource<string_type, string_adaptor> InputSourceT;

  StylesheetCompiler() 
  {
  } // StylesheetCompiler

  ~StylesheetCompiler()
  {
  } // ~StylesheetCompiler

  std::auto_ptr<Stylesheet> compile(InputSourceT& source)
  {
    error_ = "";

    std::auto_ptr<CompiledStylesheet> stylesheet(new CompiledStylesheet());

    StylesheetParser<string_type, string_adaptor> parser;
    CompilationContext<string_type, string_adaptor> context(parser, *stylesheet.get());

    StylesheetHandler<string_type, string_adaptor> stylesheetHandler(context);
    parser.setContentHandler(stylesheetHandler);
    //parser.setErrorHandler(*this);
  
    //if(entityResolver_)
    //  parser.setEntityResolver(*entityResolver_);
    try {
      parser.parse(source);
    } // try
    catch(std::exception& ex)
    {
      error_ = ex.what();
      //std::cerr << "Compilation Failed : " << ex.what() << std::endl;
      stylesheet.reset();
    } // catch

    return std::auto_ptr<Stylesheet>(stylesheet.release());
  } // compile

  const std::string& error() const
  {
    return error_;
  } // error

private:
  std::string error_;
}; // class StylesheetCompiler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_STYLESHEETCOMPILER_HPP


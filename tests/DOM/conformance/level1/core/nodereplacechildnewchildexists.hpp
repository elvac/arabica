#ifndef test_nodereplacechildnewchildexists
#define test_nodereplacechildnewchildexists


/*
This C++ source file was generated for Arabica
from the source document contained in the W3C
DOM Conformance Test Suite.
The source document contained the following notice:


Copyright (c) 2001-2004 World Wide Web Consortium,
(Massachusetts Institute of Technology, Institut National de
Recherche en Informatique et en Automatique, Keio University). All
Rights Reserved. This program is distributed under the W3C's Software
Intellectual Property License. This program is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.
See W3C License http://www.w3.org/Consortium/Legal/ for more details.

*/
/**
 *     Retrieve the second employee and replace its TWELFTH 
 *     child(address) with its SECOND child(employeeId).   After the
 *     replacement the second child should now be the one that used   
 *     to be at the third position and the TWELFTH child should be the
 *     one that used to be at the SECOND position.
* @author NIST
* @author Mary Brady
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-785887307">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-785887307</a>
*/

template<class string_type, class string_adaptor>
class nodereplacechildnewchildexists : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     nodereplacechildnewchildexists(std::string name) : baseT(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = baseT::getContentType();
    baseT::preload(contentType, "staff", true);
    }

  typedef typename Arabica::DOM::DOMImplementation<string_type, string_adaptor>  DOMImplementation;
  typedef typename Arabica::DOM::Document<string_type, string_adaptor> Document; 
  typedef typename Arabica::DOM::DocumentType<string_type, string_adaptor> DocumentType;
  typedef typename Arabica::DOM::DocumentFragment<string_type, string_adaptor> DocumentFragment; 
  typedef typename Arabica::DOM::Node<string_type, string_adaptor> Node;
  typedef typename Arabica::DOM::Element<string_type, string_adaptor> Element;
  typedef typename Arabica::DOM::Attr<string_type, string_adaptor> Attr;
  typedef typename Arabica::DOM::NodeList<string_type, string_adaptor> NodeList;
  typedef typename Arabica::DOM::NamedNodeMap<string_type, string_adaptor> NamedNodeMap;
  typedef typename Arabica::DOM::Entity<string_type, string_adaptor> Entity;
  typedef typename Arabica::DOM::EntityReference<string_type, string_adaptor> EntityReference;
  typedef typename Arabica::DOM::CharacterData<string_type, string_adaptor> CharacterData;
  typedef typename Arabica::DOM::CDATASection<string_type, string_adaptor> CDATASection;
  typedef typename Arabica::DOM::Text<string_type, string_adaptor> Text;
  typedef typename Arabica::DOM::Comment<string_type, string_adaptor> Comment;
  typedef typename Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> ProcessingInstruction;
  typedef typename Arabica::DOM::Notation<string_type, string_adaptor> Notation;

  typedef typename Arabica::DOM::DOMException DOMException;
  typedef string_type String;
  typedef string_adaptor SA;
  typedef bool boolean;


   /*
    * Runs the test case.
    */
   void runTest()
   {
      Document doc;
      NodeList elementList;
      Node employeeNode;
      NodeList childList;
      Node oldChild;
      Node newChild;
      String childName;
      Node childNode;
      int length;
      std::vector<string_type> actual;
      
      std::vector<string_type> expected;
      
      std::vector<string_type> expectedWithoutWhitespace;
      expectedWithoutWhitespace.push_back(SA::construct_from_utf8("name"));
      expectedWithoutWhitespace.push_back(SA::construct_from_utf8("position"));
      expectedWithoutWhitespace.push_back(SA::construct_from_utf8("salary"));
      expectedWithoutWhitespace.push_back(SA::construct_from_utf8("gender"));
      expectedWithoutWhitespace.push_back(SA::construct_from_utf8("employeeId"));
      
      std::vector<string_type> expectedWithWhitespace;
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("name"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("position"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("salary"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("gender"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("employeeId"));
      expectedWithWhitespace.push_back(SA::construct_from_utf8("#text"));
      
      Node replacedChild;
      doc = (Document) baseT::load("staff", true);
      elementList = doc.getElementsByTagName(SA::construct_from_utf8("employee"));
      employeeNode = elementList.item(1);
      childList = employeeNode.getChildNodes();
      length = (int) childList.getLength();
      
      if (baseT::equals(13, length)) {
          newChild = childList.item(1);
      oldChild = childList.item(11);
      expected =  expectedWithWhitespace;
      } else {
          newChild = childList.item(0);
      oldChild = childList.item(5);
      expected =  expectedWithoutWhitespace;
      }
        
    replacedChild = employeeNode.replaceChild(newChild, oldChild);
      baseT::assertSame(oldChild, replacedChild, __LINE__, __FILE__);
for (unsigned int indexN65758 = 0; indexN65758 != childList.getLength(); indexN65758++) {
          childNode = (Node) childList.item(indexN65758);
    childName = childNode.getNodeName();
      actual.push_back(childName);
        }
      baseT::assertEquals(expected, actual, __LINE__, __FILE__);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/nodereplacechildnewchildexists";
   }
};

#endif

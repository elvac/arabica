
/*
This c++ source file was generated by for Arabica
and is a derived work from the source document.
The source document contained the following notice:


Copyright (c) 2001-2003 World Wide Web Consortium,
(Massachusetts Institute of Technology, Institut National de
Recherche en Informatique et en Automatique, Keio University). All
Rights Reserved. This program is distributed under the W3C's Software
Intellectual Property License. This program is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.
See W3C License http://www.w3.org/Consortium/Legal/ for more details.

*/

#ifndef test_hc_nodeinsertbeforenewchildexists
#define test_hc_nodeinsertbeforenewchildexists

#include "dom_conf_test.hpp"

/**
 *     If the "newChild" is already in the tree, the
 *     "insertBefore(newChild,refChild)" method must first
 *     remove it before the insertion takes place.
 *     
 *     Insert a node Element ("em") that is already
 *     present in the tree.   The existing node should be 
 *     removed first and the new one inserted.   The node is
 *     inserted at a different position in the tree to assure
 *     that it was indeed inserted.
* @author Curt Arnold
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727</a>
* @see <a href="http://www.w3.org/Bugs/Public/show_bug.cgi?id=246">http://www.w3.org/Bugs/Public/show_bug.cgi?id=246</a>
*/

template<class string_type, class string_adaptor>
class hc_nodeinsertbeforenewchildexists : public DOMTestCase<string_type, string_adaptor> 
{
   public: 
     hc_nodeinsertbeforenewchildexists(std::string name) : DOMTestCase(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = getContentType();
    preload(contentType, "hc_staff", true);
    }

  typedef typename DOMTestCase<string_type, string_adaptor> baseT;
  using baseT::DOMImplementation;
  using baseT::Document; 
  using baseT::DocumentType;
  using baseT::DocumentFragment; 
  using baseT::Node;
  using baseT::Element;
  using baseT::Attr;
  using baseT::NodeList;
  using baseT::NamedNodeMap;
  using baseT::Entity;
  using baseT::EntityReference;
  using baseT::CharacterData;
  using baseT::CDATASection;
  using baseT::Text;
  using baseT::Comment;
  using baseT::ProcessingInstruction;
  using baseT::Notation;

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
      Node refChild;
      Node newChild;
      Node child;
      String childName;
      Node insertedNode;
      std::vector<string_type> expected;
      expected.push_back(SA::construct_from_utf8("strong"));
      expected.push_back(SA::construct_from_utf8("code"));
      expected.push_back(SA::construct_from_utf8("sup"));
      expected.push_back(SA::construct_from_utf8("var"));
      expected.push_back(SA::construct_from_utf8("em"));
      expected.push_back(SA::construct_from_utf8("acronym"));
      
      std::vector<string_type> result;
      
      int nodeType;
      doc = (Document) load("hc_staff", true);
      elementList = doc.getElementsByTagName(SA::construct_from_utf8("p"));
      employeeNode = elementList.item(1);
      childList = ((Element) /*Node */employeeNode).getElementsByTagName(SA::construct_from_utf8("*"));
      refChild = childList.item(5);
      newChild = childList.item(0);
      insertedNode = employeeNode.insertBefore(newChild, refChild);
      for (int indexN65676 = 0; indexN65676 != childList.getLength(); indexN65676++) {
          child = (Node) childList.item(indexN65676);
    nodeType = (int) child.getNodeType();
      
      if (equals(1, nodeType)) {
          childName = child.getNodeName();
      result.push_back(childName);
      }
      }
      assertEquals(expected, result);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/hc_nodeinsertbeforenewchildexists";
   }
};

#endif
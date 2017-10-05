


#include <stdio.h>
#include <string.h>
#include <libxml2/libxml/parser.h>


char buffer[7][50];


static void printElem(xmlNode *a_node) {
  xmlNode *cur_node = NULL;
  xmlChar *content;
  unsigned char *look;
  look = (unsigned char *) "ref";

  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      printf("node name: %s\n", cur_node->name);
    
      xmlAttr *attr = cur_node->properties;
      while (attr){
	content = xmlGetProp(cur_node, look);
	if( content !=NULL){
	  printf("Content: %s\n", content);
	}
	xmlFree(content);
      	attr = attr->next;
      }
    }
    /*
    else if (cur_node->type == XML_TEXT_NODE){
      xmlChar *con = xmlNodeGetContent(cur_node);
      printf("val: %s", con);
      xmlFree(con);
      }*/
    
    //child = cur_node->children;
    //if(child->name == "nd"){
    if(!xmlStrcmp(cur_node->name, (const xmlChar *)"tag")){
      printf("\n");
    }
    printElem(cur_node->children);
  
  }
}



int main(int argc, char **argv)
{
  xmlDoc         *document;
  xmlNode        *root;//, *first_child, *node;
  char           *quad;
  /*
  if (argc < 2) {
    fprintf(stderr, "Usage: %s quad_and_comp_sci.xml\n", argv[0]);
    return 1;
    }*/
  // quad = argv[1];
  quad = "quad.xml";
  //int j =0;
  
  document = xmlReadFile(quad, NULL, 0);
  if(document ==NULL) {
    printf("error: could not parse file %s\n", argv[1]);
  }
  
  root = xmlDocGetRootElement(document);
  //fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);

  printElem(root);
    /*
  first_child = root->children;
  for (node = first_child; j<20; node = node->next) {
    fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
    j++;
    
    }*/
  fprintf(stdout, "...\n");

  xmlFreeDoc(document);

  xmlCleanupParser();
  return 0;
}

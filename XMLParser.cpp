#include "XMLScene.h"
#include "XMLParser.h"
#include "CGFappearance.h"
#include "ExampleObject.h"
#include "CGFapplication.h"
#include "CGFaxis.h"
#include <strings.h>
#include <iostream>

XMLParser::XMLParser(char *filename) {
    
    // Read XML from file
    
    doc=new TiXmlDocument( filename );
    bool loadOkay = doc->LoadFile();
    
    if ( !loadOkay )
    {
        printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
        exit( 1 );
    }
    
    TiXmlElement* anfElement= doc->FirstChildElement( "anf" );
    
    if (anfElement == NULL)
    {
        printf("Main anf block element not found! Exiting!\n");
        exit(1);
    }
    
    globalsElement = anfElement->FirstChildElement( "globals" );
    
    
    // Globals
    // An example of well-known, required nodes
    
    if (globalsElement == NULL)
        printf("globals block not found!\n");
    else
    {
        printf("Processing global elements:\n");
        /** DRAWING PROPERTIES **/
        TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
        if (drawingElement) {
            /**
             * TO DO: verificar se os inputs estão correctos
             */
            
            // Procura os elementos dentro do drawing
            drawingMode = (char *) drawingElement->Attribute("mode");
            
            shading = (char *) drawingElement->Attribute("shading");
            
            char * background = (char *) drawingElement->Attribute("background");
            sscanf(background, "%f %f %f %f",&backgroundColor[0],&backgroundColor[1],
                   &backgroundColor[2],&backgroundColor[3]);
            
            
        }
        else
            printf("Drawing element not found\n");
        
        /** CULLING PROPERTIES **/
        TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
        if (cullingElement) {
            face = (char *) drawingElement->Attribute("face");
            order = (char *) drawingElement->Attribute("order");
        }
        else
            printf("culling not found\n");
        
        /** LIGHTING PROPERTIES **/
        
        TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");
        if (lightingElement) {
            char * doublesideTemp; char* localTemp; char* enabledTemp; char* ambientTemp;
            
            doublesideTemp = (char *) lightingElement->Attribute("doublesided");
            (checkTrue(doublesideTemp)) ? doublesided=true : doublesided=false;
            
            localTemp = (char *) lightingElement->Attribute("local");
            (checkTrue(doublesideTemp)) ? local=true : local=false;
            
            enabledTemp = (char *) lightingElement->Attribute("enabled");
            (checkTrue(doublesideTemp)) ? enabled=true : enabled=false;
            
            ambientTemp = (char *) lightingElement->Attribute("ambient");
            sscanf(ambientTemp, "%f %f %f %f",&ambient[0],&ambient[1],
                   &ambient[2],&ambient[3]);
            
        }
        else
            printf("lighting not found\n");
    }
    
    // Other blocks could be validated/processed here
    
    
    // graph section
    if (graphElement == NULL)
        printf("Graph block not found!\n");
    else
    {
        char *prefix="  -";
        TiXmlElement *node=graphElement->FirstChildElement();
        
        while (node)
        {
            printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
            TiXmlElement *child=node->FirstChildElement();
            while (child)
            {
                if (strcmp(child->Value(),"Node")==0)
                {
                    // access node data by searching for its id in the nodes section
                    
                    TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));
                    
                    if (noderef)
                    {
                        // print id
                        printf("  - Node id: '%s'\n", child->Attribute("id"));
                        
                        // prints some of the data
                        printf("    - Material id: '%s' \n", noderef->FirstChildElement("material")->Attribute("id"));
                        printf("    - Texture id: '%s' \n", noderef->FirstChildElement("texture")->Attribute("id"));
                        
                        // repeat for other leaf details
                    }
                    else
                        printf("  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n", child->Attribute("id"));
                    
                }
                if (strcmp(child->Value(),"Leaf")==0)
                {
                    // access leaf data by searching for its id in the leaves section
                    TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));
                    
                    if (leaf)
                    {
                        // it is a leaf and it is present in the leaves section
                        printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));
                        
                        // repeat for other leaf details
                    }
                    else
                        printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
                }
                
                child=child->NextSiblingElement();
            }
            node=node->NextSiblingElement();
        }
    }
    
}

XMLParser::~XMLParser() {
    delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLParser::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val) {
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions

    TiXmlElement *child=parent->FirstChildElement();
    int found=0;
    
    while (child && !found)
        if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
            found=1;
        else
            child=child->NextSiblingElement();
    
    return child;
}





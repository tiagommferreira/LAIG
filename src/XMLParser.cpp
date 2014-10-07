#include "XMLScene.h"
#include "XMLParser.h"
#include "CGFappearance.h"
#include "CGFapplication.h"
#include "CGFaxis.h"

#include <iostream>

XMLParser::XMLParser() {
    //const char *p = "/Users/ricardo/Documents/compiledProject/CGFlib/CGFexample/data/tiny.xml";
     const char *p = "tiny.xml";
    // Read XML from file
    
    doc=new TiXmlDocument(p );
    bool loadOkay = doc->LoadFile();
    
    if ( !loadOkay )
    {
        printf( "Could not load file '%s'. Error='%s'. Exiting.\n", p, doc->ErrorDesc() );
        exit( 1 );
    }
    
    anfElement= doc->FirstChildElement( "anf" );
    
    if (anfElement == NULL)
    {
        printf("Main anf block element not found! Exiting!\n");
        exit(1);
    }
    
    globalsElement = anfElement->FirstChildElement( "globals" );
    
    cout << "_____ GLOBALS INFO _____" << endl;
    // Globals
    
    if (globalsElement == NULL)
        printf("globals block not found!\n");
    else
    {
        global = new Globals();
        
        /** DRAWING PROPERTIES **/
        TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
        if (drawingElement) {
            
            // Procura os elementos dentro do drawing
            
            cout << "drawing information" << endl;
            
            char *drawingMode = (char *) drawingElement->Attribute("mode");
            char *shading = (char *) drawingElement->Attribute("shading");
            char * background = (char *) drawingElement->Attribute("background");
        
            global->setDrawingMode(drawingMode);
            global->setShading(shading);
            global->setBackgroundColor(background);
            
            cout << "end of parsing drawing information" << endl;
            
        }
        else
            printf("Drawing element not found\n");
        
        /** CULLING PROPERTIES **/
        TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
        if (cullingElement) {
            cout << "culling information" << endl;
            char *face = (char *) cullingElement->Attribute("face");
            char *order = (char *) cullingElement->Attribute("order");
            
            global->setFace(face);
            global->setOrder(order);
            cout << "end of parsing culling information" << endl;
        }
        else
            printf("culling not found\n");
        
        /** LIGHTING PROPERTIES **/
        
        TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");
        if (lightingElement) {
            cout << "lighting information" << endl;
            
            char *doublesided = (char *) lightingElement->Attribute("doublesided");
            char *local = (char *) lightingElement->Attribute("local");
            char* enabled = (char *) lightingElement->Attribute("enabled");
            char *ambientTemp = (char *) lightingElement->Attribute("ambient");
            
            global->setDoublesided(doublesided);
            global->setLocal(local);
            global->setEnable(enabled);
            global->setAmbient(ambientTemp);
            
            cout << "end of parsing lighting information" << endl;
        }
        else
            printf("lighting not found\n");
    }
    
    // Camera
    cout << endl << "_____ CAMERA INFO _____" << endl;
    camerasElement = anfElement->FirstChildElement( "cameras" );
    if(camerasElement){
        TiXmlElement* camera=camerasElement->FirstChildElement();
        char *initial = (char *)camerasElement->Attribute("initial");
        
        while(camera) {
            if (strcmp(camera->Value(),"ortho")==0) {
                cout << "ortho cam found" << endl;
                Camera * orthoCam=new Camera();
                orthoCam->setInitial(initial);
                orthoCam->setType(1);
                
                // ortho
                char * orthoId = (char*) camera->Attribute("id");
                orthoCam->setId(orthoId);
                
                char * orthoNearTemp = (char *) camera->Attribute("near");
                orthoCam->setOrthoNear(atof(orthoNearTemp));
                
                char * orthoFarTemp = (char *) camera->Attribute("far");
                orthoCam->setOrthoFar(atof(orthoFarTemp));
                
                char * orthoLeftTemp = (char *) camera->Attribute("left");
                orthoCam->setOrthoLeft(atof(orthoLeftTemp));
                
                char * orthoRightTemp = (char *) camera->Attribute("right");
                orthoCam->setOrthoRight(atof(orthoRightTemp));
                
                char * orthoTopTemp = (char *) camera->Attribute("top");
                orthoCam->setOrthoTop(atof(orthoTopTemp));
                
                char * orthoBottomTemp = (char *) camera->Attribute("bottom");
                orthoCam->setOrthoBottom(atof(orthoBottomTemp));
                
                char * directionTemp = (char *) camera->Attribute("direction");
                orthoCam->setOrthoDirection(directionTemp[0]);
                
                cameras.push_back(orthoCam);
                
                cout << "end of parsing ortho informaton" << endl;
            } else{
                Camera * perspCam=new Camera();
                perspCam->setInitial(initial);
                perspCam->setType(0);
                
                cout << "Perspective camera found" << endl;
                // perspective
                char * perspecId = (char *) camera->Attribute("id");
                perspCam->setId(perspecId);

				cout << "id done" << endl;
                
                char * perspNearTemp = (char *) camera->Attribute("near");
                perspCam->setNearPerspec(atof(perspNearTemp));
                
				cout << "near done" << endl;

                char * perspFarTemp = (char *) camera->Attribute("far");
                perspCam->setFarPerspec(atof(perspFarTemp));
                
				cout << "far done" << endl;

                char * perspAngleTemp = (char *) camera->Attribute("angle");
                perspCam->setAnglePerspec(atof(perspAngleTemp));
                
				cout << "angle done" << endl;

                char *posTemp = (char *) camera->Attribute("pos");
                perspCam->setPerspPos(posTemp);
                
				cout << "pos done" << endl;

                char *targetTemp = (char *) camera->Attribute("target");
                perspCam->setPerspTarget(targetTemp);	

				cout << "target done" << endl;
                
                cout << "end of parsing perspective information" << endl;
                
                cameras.push_back(perspCam);
            }
            camera = camera->NextSiblingElement();
        }
        
    }else {
        cout << "Cameras element wasnt found\n";
    }
    
    
    //lights
    cout << endl << "_____ LIGHTS INFO _____" << endl;
    lightsElement = anfElement->FirstChildElement( "lights" );
    
    if(lightsElement){
        TiXmlElement* light=lightsElement->FirstChildElement();
       
        while(light) {
			Light *lightTemp=new Light();
                
			cout << "Light found" << endl;
			
            char * idLight = (char *) light->Attribute("id");
            lightTemp->setID(idLight);
            
            char * type = (char *) light->Attribute("type");
            lightTemp->setType(type);

            char * enabled = (char *) light->Attribute("enabled");
            lightTemp->setEnabled(enabled);

            char * marker = (char *) light->Attribute("marker");
            lightTemp->setMarker(marker);

            char *posTemp = (char *) light->Attribute("pos");
            lightTemp->setPosition(posTemp);
			
			//ATTRIBUTES
			TiXmlElement* attr = light->FirstChildElement();

			while(attr) {

				char *attribute;

				if(strcmp(attr->Attribute("type"), "ambient") == 0) {
					attribute = (char *) attr->Attribute("value");
					lightTemp->setAmbientComponent(attribute);
				}
				else if(strcmp(attr->Attribute("type"), "diffuse") == 0) {
					attribute = (char *) attr->Attribute("value");
					lightTemp->setDiffuseComponent(attribute);
				}
				else if(strcmp(attr->Attribute("type"), "ambient") == 0) {
					attribute = (char *) attr->Attribute("value");
					lightTemp->setSpecularComponent(attribute);
				}

				attr = attr->NextSiblingElement();
			}
                
            cout << "end of parsing perspective information" << endl;
                
            //lights.push_back(lightTemp);
			
			//cout << "Ambient: " << endl;
			//cout << lightTemp->getAmbientComponent()[0] << ", " << lightTemp->getAmbientComponent()[1] << ", " << lightTemp->getAmbientComponent()[2] << ", " << lightTemp->getAmbientComponent()[3] << endl << endl;

			//cout << "Diffuse: " << endl;
			//cout << lightTemp->getDiffuseComponent()[0] << ", " << lightTemp->getDiffuseComponent()[0] << ", " << lightTemp->getDiffuseComponent()[2] << ", " << lightTemp->getDiffuseComponent()[3] << endl << endl;

			light = light->NextSiblingElement();
		}
	}
}
    
    
    // Other blocks could be validated/processed here
    
    /*
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
    }*/
    


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





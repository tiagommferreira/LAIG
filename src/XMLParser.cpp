#include "XMLScene.h"
#include "XMLParser.h"
#include "CGFappearance.h"
#include "CGFapplication.h"
#include "CGFaxis.h"

#include <iostream>

XMLParser::XMLParser() {
	const char *p = "tiny.anf";
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
				cout <<"ortho cam found" << endl;
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

			if(strcmp(type,"spot") == 0){
				char * target = (char *) light->Attribute("target");
				lightTemp->setTarget(target);

				char * angle = (char *) light->Attribute("angle");
				lightTemp->setAngle(atof(angle));

				char * exponent = (char *) light->Attribute("exponent");
				lightTemp->setExponent(atof(exponent));
			}

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

			lights.push_back(lightTemp);
			light = light->NextSiblingElement();
		}
	}

	// graph section
	graphElement = anfElement->FirstChildElement( "graph" );
	if(graphElement==NULL){
		cout << "Graph block not found!" << endl;
	} else {
		cout << endl << "_____ GRAPH INFO _____" << endl;;
		TiXmlElement *node=graphElement->FirstChildElement();
		char * root = (char *)graphElement->Attribute("rootid");
		rootid = root;
		while(node){
			cout << endl <<"specific node found" << endl;

			char * id = (char *)node->Attribute("id");

			Node* currentNode;
			if(graph.find(id) != graph.end()) {
				currentNode = graph.find(id)->second;
			}
			else {
				currentNode = new Node();
				currentNode->setId(id);
			}


			TiXmlElement *transforms=node->FirstChildElement("transforms");
			if(transforms==NULL){
				cout << "transformations not found " << endl;
			}else {
				TiXmlElement *transform=transforms->FirstChildElement();
				if(transform==NULL){
					cout << "specific transform not found " << endl;
				}else {
					while(transform){
						cout << "transform found" << endl;
						Transform *transforTemp = new Transform();

						char * type = (char *) transform->Attribute("type");
						transforTemp->setType(type);

						if(strcmp(type,"translate")==0){
							char * to = (char *) transform->Attribute("to");
							transforTemp->setTo(to);
						} else if(strcmp(type,"rotate")==0){
							char * axis = (char *) transform->Attribute("axis");
							transforTemp->setAxis(axis[0]);
							char * angle = (char *) transform->Attribute("angle");
							transforTemp->setAngle(atof(angle));
						} else if(strcmp(type,"scale")==0){
							char * factor = (char *) transform->Attribute("factor");
							transforTemp->setFactor(factor);
						}
						currentNode->addTransform(transforTemp);
						transform = transform->NextSiblingElement();
					}

					// transforms all read
					currentNode->setMatrix();
				}

			}

			TiXmlElement *appearence = node->FirstChildElement("appearanceref");
			if(appearence==NULL){
				cout << "appearence not found " << endl;
			} else {
				cout << "appearence found" << endl;
				char * apearenceId = (char *) appearence->Attribute("id");
				currentNode->setAppearence(apearenceId);
			}

			TiXmlElement *primitives = node->FirstChildElement("primitives");
			if(primitives==NULL){
				cout << "primitives not found" << endl;
			} else {
				TiXmlElement *primitive = primitives->FirstChildElement();
				if(primitive==NULL){
					cout << "specific primitive not found" << endl;
				} else {
					while(primitive) {

						Primitive *primitiveTemp = new Primitive();
						primitiveTemp->setValue((char*)primitive->Value());
						cout << "specific primitive found:" << primitive->Value() << endl;
						if(strcmp(primitive->Value(),"rectangle")==0) {
							char* xy1 = (char*) primitive->Attribute("xy1");
							char* xy2 = (char*) primitive->Attribute("xy2");

							primitiveTemp->setXY1(xy1);
							primitiveTemp->setXY2(xy2);

						}
						else if(strcmp(primitive->Value(),"triangle")==0) {
							char* xyz1 = (char*) primitive->Attribute("xyz1");
							char* xyz2 = (char*) primitive->Attribute("xyz2");
							char* xyz3 = (char*) primitive->Attribute("xyz3");

							primitiveTemp->setXYZ1(xyz1);
							primitiveTemp->setXYZ2(xyz2);
							primitiveTemp->setXYZ3(xyz3);

						}
						else if(strcmp(primitive->Value(),"cylinder")==0) {
							char* base = (char*) primitive->Attribute("base");
							char* top = (char*) primitive->Attribute("top");
							char* height = (char*) primitive->Attribute("height");
							char* slices = (char*) primitive->Attribute("slices");
							char* stacks = (char*) primitive->Attribute("stacks");

							primitiveTemp->setBase(atof(base));
							primitiveTemp->setTop(atof(top));
							primitiveTemp->setHeight(atof(height));
							primitiveTemp->setSlices(atof(slices));
							primitiveTemp->setStacks(atof(stacks));

						} else if(strcmp(primitive->Value(),"sphere")==0){
							char* radius = (char*) primitive->Attribute("radius");
							char* slices = (char*) primitive->Attribute("slices");
							char* stacks = (char*) primitive->Attribute("stacks");

							primitiveTemp->setRadius(atof(radius));
							primitiveTemp->setSlices(atof(slices));
							primitiveTemp->setStacks(atof(stacks));

						} else if(strcmp(primitive->Value(),"torus")==0){
							char* inner = (char*) primitive->Attribute("inner");
							char* outer = (char*) primitive->Attribute("outer");
							char* slices = (char*) primitive->Attribute("slices");
							char* loops = (char*) primitive->Attribute("loops");

							primitiveTemp->setInner(atof(inner));
							primitiveTemp->setOutter(atof(outer));
							primitiveTemp->setSlices(atof(slices));
							primitiveTemp->setLoops(atof(loops));
						}

						currentNode->addPrimitive(primitiveTemp);
						primitive = primitive->NextSiblingElement();
					}
				}
			}

			TiXmlElement *descendents=node->FirstChildElement("descendants");
			if(descendents==NULL){
				cout << "No descendents found" << endl;
			}else{
				cout << "start descendents parser" << endl;

				TiXmlElement *noderef = descendents->FirstChildElement();
				while(noderef){
					cout << "specific descendent found " << endl;
					//Adds the id of descendents to a vector of descendents of the analyzed node and afterwards sets it to referencing
					//a specific node

					char *id = (char*) noderef->Attribute("id");
					Node * descNode = new Node();
					descNode->setId(id);
					currentNode->setDescendents(descNode);
					graph[descNode->getId()] = descNode;
					noderef = noderef->NextSiblingElement();
				}
				cout << "end of descendents" << endl;
			}
			/*
			 * TODO adicionar ao fim os respectivos nodes ao respectivo id.
			 * ciclo for a comparar ids com os respectivos assim so corre uma vez no inicio e dp ja tem o id para a referencia
			 */
			cout << "end of specific node" << endl;
			graph[currentNode->getId()] = currentNode;
			node = node->NextSiblingElement();
		}
		cout << "Graph block element end" << endl;
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





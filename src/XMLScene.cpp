#include "XMLScene.h"
#include "XMLParser.h"
#include <string.h>
#include <iostream>
#include <math.h>

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val) {
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();
	return child;
}

void XMLScene::init() {
	/** Parses the information from xml to c++ **/
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");
	parser = new XMLParser();
	camera = parser->getCameras()[0]->getInitial();
	socket = new PlogSocket();
	gameState = new Game();


	cout <<  endl << endl << endl <<"_____ OPEN GL ______" << endl << endl;

	cout << "lighting properties" << endl;
	//LIGHTING PROPERTIES
	glEnable(GL_LIGHTING);
	if((strcmp (parser->getGlobals()->getEnabled(),"true")==0)){
		glEnable(GL_LIGHTING);
	}
	if((strcmp (parser->getGlobals()->getLocal(),"true")==0)){
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	}
	if((strcmp (parser->getGlobals()->getDoublesided(),"true")==0)){
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,parser->getGlobals()->getAmbientLight());

	addLights();
	glEnable(GL_NORMALIZE);


	cout << "__globals__" << endl << endl;
	/* GLOBALS */
	cout << "culling properties" << endl;
	// CULLING PROPERTIES
	if((strcmp (parser->getGlobals()->getOrder(),(char*)"cw")==0)){
		glFrontFace(GL_CW);
	}else {
		glFrontFace(GL_CCW);
	}

	// also has the possibility to be none
	if((strcmp(parser->getGlobals()->getFace(),"front")==0)){
		glCullFace(GL_FRONT);
	}else if((strcmp (parser->getGlobals()->getFace(),"back")==0)){
		glCullFace(GL_BACK);
	}

	cout << "drawing properties" << endl;
	//DRAWING PROPERTIES
	/**
	 * TODO verificar se isto é aqui ou no update
	 */
	if((strcmp (parser->getGlobals()->getShading(),"flat")==0)){
		glShadeModel(GL_FLAT);
	}else {
		glShadeModel(GL_SMOOTH);
	}

	if((strcmp (parser->getGlobals()->getDrawingMode(),"fill")==0)){
		fill = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else if(strcmp(parser->getGlobals()->getDrawingMode(),"point")==0){
		point = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}else if(strcmp (parser->getGlobals()->getDrawingMode(),"line")==0){
		wire = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	cout << "set background "<< endl;
	//background color
	float* backColor = parser->getGlobals()->getBackgroundColor();
	glClearColor(backColor[0],backColor[1],backColor[2],backColor[3]);

	// initialize appearences;
	setNodesAppearances();

	setUpdatePeriod(30);

	map<char*,Node*> temp = parser->getGraph();
	map<char*,Node*>::iterator it=temp.begin();
	for(unsigned int i=0;i<temp.size();i++,it++){
		if(strcmp(it->first,"tabuleiro")==0){
			this->board = (Board*)it->second->getPrimitives()[0];
			states.push_back(board->boardToString());
			break;
		}
	}

	socket->connectSocket();
	isFilmActive=false;
	finishAnimation=false;
	cout << "start updating" << endl;
}

void XMLScene::update(unsigned long t) {
	map<char*,Node*> temp = parser->getGraph();
	map<char*,Node*>::iterator it=temp.begin();
	for(;it!=temp.end();it++){
		it->second->update();
	}
}

void XMLScene::display() {
	sceneVar=0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();
	// Draw (and update) light
	drawLights();


	if(isFilmActive) {
		time_t now;
		time(&now);
		double seconds = difftime(now,lastAnimationTime);
		cout << "seconds: " << seconds << endl;
		if(seconds > 1) {
			if(currentAnimationState+2 <= states.size()) {
				board->updateBoard(pointsClickedOverTime[currentAnimationState]);
				lastAnimationTime=now;
				currentAnimationState++;
			}else {
				isFilmActive=false;
			}
		}
	}

	if(finishAnimation) {
		time_t now;
		time(&now);
		double seconds = difftime(now,lastAnimationTime);
		cout << "seconds: " << seconds << endl;
		if(seconds > 4) {
			board->updateBoard2((char*) states[0].c_str());
			states.clear();
			states.push_back(board->boardToString());
			pointsClickedOverTime.clear();
			finishAnimation=false;
			gameState->setCurrentPlayer(1);
		} else {
			printMessage();
		}
	}

	glPushMatrix();
	glPushName(-1);
	map<char*,Node*> temp = parser->getGraph();
	map<char*,Node*>::iterator it=temp.begin();

	for(unsigned int i=0;i<temp.size();i++,it++){
		if(strcmp(parser->getRootid(),it->second->getId())==0){
			it->second->draw();
			break;
		}
	}

	glPopMatrix();
	swapPosition();
	glutSwapBuffers();
}

XMLScene::~XMLScene() {
	delete(shader);
}

void XMLScene::addLights(){
	vector<Light*> lights = parser->getLights();
	for(unsigned int i=0;i<lights.size();i++) {
		//direcao se for luz omni
		float spotDir[3]={0,0,0};
		//init posicao com o o ultimo valor a 1
		float lightPos[4] = {lights[i]->getPosition()[0],lights[i]->getPosition()[1],lights[i]->getPosition()[2],1.0};

		if(strcmp(lights[i]->getType(),(char*) "spot")==0) {
			//calcular target
			float finalTarget[3] ={lights[i]->getTarget()[0] - lights[i]->getPosition()[0],
					lights[i]->getTarget()[1]- lights[i]->getPosition()[1],
					lights[i]->getTarget()[2]- lights[i]->getPosition()[2]};
			//normalizar vetor
			float unit = sqrt(finalTarget[0] * finalTarget[0] + finalTarget[1] * finalTarget[1] + finalTarget[2] * finalTarget[2]);
			for (int j = 0; j < 3; j++) {
				finalTarget[j] = finalTarget[j] / unit;
				spotDir[j] = finalTarget[j];
			}
			glLightf(GL_LIGHT0 + i,GL_SPOT_CUTOFF,lights[i]->getAngle());
			glLightf(GL_LIGHT0 + i,GL_SPOT_EXPONENT,lights[i]->getExponent());
			glLightfv(GL_LIGHT0 + i,GL_SPOT_DIRECTION,lights[i]->getTarget());
		}

		CGFlight *currentLight = new CGFlight(i+GL_LIGHT0,lightPos, spotDir);
		currentLight->setAmbient(lights[i]->getAmbientComponent());
		currentLight->setDiffuse(lights[i]->getDiffuseComponent());
		currentLight->setSpecular(lights[i]->getSpecularComponent());
		if(strcmp(lights[i]->getEnabled(),(char*)"true")==0){
			currentLight->enable();
			cout << i << "enabled" << endl;
		}else {
			currentLight->disable();
			cout << i << "disabled" << endl;
		}

		currentLight->update();


		this->lights.push_back(currentLight);
	}
}

void XMLScene::drawLights(){
	vector<Light*> tempLights=parser->getLights();
	for(unsigned int i=0;i<tempLights.size();i++){
		this->lights[i]->draw();
	}
}

void XMLScene::setNodesAppearances() {
	this->appearances = vector<CGFappearance*>();
	for(unsigned int i=0;i<parser->getAppearances().size();i++){
		CGFappearance *currentAppearance = new CGFappearance(
				parser->getAppearances()[i]->getAmbientComponent(),
				parser->getAppearances()[i]->getDiffuseComponent(),
				parser->getAppearances()[i]->getSpecularComponent(),
				parser->getAppearances()[i]->getShininess()
		);

		if(parser->getAppearances()[i]->getTextureref()) {
			if(strcmp("inherit",parser->getAppearances()[i]->getTextureref()) == 0){

			}else {
				char * filePath = (char*)"";
				for(unsigned int j=0;j<parser->getTextures().size();j++){
					if(strcmp(parser->getAppearances()[i]->getTextureref(),parser->getTextures()[j]->getId())==0){
						filePath = parser->getTextures()[j]->getFile();
						cout << filePath << endl;
					}
				}
				if(strcmp(filePath, "")) {
					CGFtexture * currentTexture = new CGFtexture(filePath);
					currentAppearance->setTexture(currentTexture);
				}
			}
		}
		this->appearances.push_back(currentAppearance);
	}

	map<char*,Node*> graph = parser->getGraph();
	map<char*,Node*>::iterator it = graph.begin();
	map<char*,Node*>::iterator ite = graph.end();

	for(;it!=ite;it++){
		for(unsigned int i=0; i<parser->getAppearances().size();i++) {
			if(strcmp(it->second->getAppearenceRef(),parser->getAppearances()[i]->getId())==0){
				it->second->setAppearance(appearances[i]);
				cout << "here" << endl;
				setNodeChildApp(it->second);
			}
		}
	}

}

void XMLScene::setNodeChildApp(Node* parent) {
	for(unsigned int i = 0; i < parent->getDescendents().size(); i++) {
		if(strcmp(parent->getDescendents()[i]->getAppearenceRef(), "inherit") == 0 || strcmp(parent->getDescendents()[i]->getAppearenceRef(),"")==0) {
				parent->getDescendents()[i]->setAppearance(parent->getAppearance());
				setNodeChildApp(parent->getDescendents()[i]);
		}
	}
}

void XMLScene::toggleLight(int lightId){
	if(strcmp(parser->getLights()[lightId]->getEnabled(),"true")==0){
		parser->getLights()[lightId]->setEnabled((char*)"false");
		cout << "now is false" << endl;
		lights[lightId]->disable();
		lights[lightId]->update();
	} else if(strcmp(parser->getLights()[lightId]->getEnabled(),"false")==0){
		parser->getLights()[lightId]->setEnabled((char*)"true");
		cout << "now is true" << endl;
		lights[lightId]->enable();
		lights[lightId]->update();
	}
}

void XMLScene::addCameras(char* id){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	vector<Camera*>cameraTemp = parser->getCameras();
	for(unsigned int i=0;i<cameraTemp.size();i++){
		if(strcmp(id,cameraTemp[i]->getId())==0){
			if(cameraTemp[i]->getType()==0){
				//perspective
				gluPerspective(cameraTemp[i]->getPerspecAngle(), 1, cameraTemp[i]->getPerspecNear(), cameraTemp[i]->getPerspecFar());
				gluLookAt(cameraTemp[i]->getPerspecPos()[0], cameraTemp[i]->getPerspecPos()[1], cameraTemp[i]->getPerspecPos()[2], cameraTemp[i]->getPerspecTarget()[0], cameraTemp[i]->getPerspecTarget()[1], cameraTemp[i]->getPerspecTarget()[2], 0, 1, 0);
			}else{
				//orthogonal
				glOrtho(
						cameraTemp[i]->getOrthoLeft(),
						cameraTemp[i]->getOrthoRight(),
						cameraTemp[i]->getOrthoBottom(),
						cameraTemp[i]->getOrthoTop(),
						cameraTemp[i]->getOrthoNear(),
						cameraTemp[i]->getOrthoFar()
				);
				switch (cameraTemp[i]->getOrthoDirection()) {
				case 'x':{
					glRotated(-90,0,1,0);
				}
				break;
				case 'y':{
					glRotated(90,1,0,0);
				}
				break;
				case 'z':{

				}
				break;
				default:
					break;
				}
			}
		}
	}
	glMatrixMode(GL_MODELVIEW);
}

void XMLScene::setDrawingType(char* drawingType){
	if(strcmp(drawingType,(char*)"fill")==0){
		cout << "fill set" << endl;
		fill = true;
		wire = false;
		point = false;
	} else if(strcmp(drawingType,(char*)"point")==0){
		cout << "point set" << endl;
		point = true;
		wire = false;
		fill = false;
	} else  {
		cout << "line set" << endl;
		wire = true;
		fill = false;
		point = false;
	}
}

void XMLScene::addPoint(int coordinate) {
	if(isFilmActive || finishAnimation) {
		return;
	}
	if(pointsClicked.size()==4) // 2 pontos preenchidos
	{
		pointsClicked.clear();
	}

	if(pointsClicked.size()==2) // um ponto
	{
		//verificar isto
		if(this->board->getCurrentState()[pointsClicked[0]][pointsClicked[1]]->getNumberOfPieces()==0){
			pointsClicked.clear();
		}
		//se clicar numa peca do adversário
		else if (this->board->getCurrentState()[pointsClicked[0]][pointsClicked[1]]->getPlayerNumber() !=
				gameState->getCurrentPlayer()){
			pointsClicked.clear()	;
		}
	}

	this->pointsClicked.push_back(coordinate);
	//request prolog availability for hte current piece
	if(pointsClicked.size()==2)
	{
		cout << "answer requested to prolog\n";
		socket->sendMessage((char*)createPieceCommand().c_str());
		char *answer;
		answer = socket->receiveMessage();
		board->changeColours(answer);
	}
}

void XMLScene::swapPosition() {
	if(pointsClicked.size()==4 &&
			!(pointsClicked[0] == pointsClicked[2] && pointsClicked[1] == pointsClicked[3]) // nao ser a mesma peça
	){

		socket->sendMessage((char*)createPlayCommand().c_str());

		char *answer;
		answer = socket->receiveMessage();

		if(checkBoardChanges(answer)) //se houver alteracoes, faz update
		{
			board->updateBoard(pointsClicked);

			states.push_back(board->boardToString());
			pointsClickedOverTime.push_back(pointsClicked);
			if(vsPc) {
				doPCMove();
			}
			bool isOver = board->isOver(gameState->getCurrentPlayer());
			if(isOver) {
				finishAnimation=true;
				time(&lastAnimationTime);
			}
			gameState->setCurrentPlayer((gameState->getCurrentPlayer())%2+1);
		}
		board->resetBoardColours();
		pointsClicked.clear();

	}
}

bool XMLScene::checkBoardChanges(char * answer) {
	stringstream comparingValue;
	comparingValue  << board->boardToString() << ".";

	if(strcmp(comparingValue.str().c_str(),answer)==0){
		return false;
	} else {

		return true;
	}

}

string XMLScene::createPieceCommand(){
	stringstream command;
	command << "verificarPeca(";
	command << gameState->getCurrentPlayer() << "," << board->boardToString() << "," << pointsClicked[1] << ","
			<< pointsClicked[0] << "," << 0 << ","<< 0 << ",[], NovaLista).";
	return command.str();
}

string XMLScene::createPlayCommand() {
	stringstream command;

	command << "comando(";
	command << board->boardToString() << ",";
	command << gameState->getCurrentPlayer() << ",";

	if( (board->getCurrentState()[pointsClicked[0]][pointsClicked[1]]->getPlayerNumber() == board->getCurrentState()[pointsClicked[2]][pointsClicked[3]]->getPlayerNumber())
			&& pointsClicked[0]<4 && pointsClicked[0]>0 && pointsClicked[2]<4 && pointsClicked[2]>0
			&& pointsClicked[1]<6 && pointsClicked[1]>0 && pointsClicked[3]<6 && pointsClicked[3]>0) {
		command << "2" << ",";
	}
	else {
		command << "1" << ",";
	}

	command << pointsClicked[1] << "," << pointsClicked[3] << "," << pointsClicked[0] << "," << pointsClicked[2] << ",";
	command << "Tabuleiro).";

	return command.str();
}

void XMLScene::undoMove() {
	if(states.size()>1){
		gameState->setCurrentPlayer((gameState->getCurrentPlayer()%2)+1);
		states.erase(states.begin()+states.size()-1);
		pointsClickedOverTime.erase(pointsClickedOverTime.begin()+pointsClickedOverTime.size()-1);
		board->updateBoard2((char*) states[states.size()-1].c_str());
	}
}

void XMLScene::gameView(){
	if(states.size()>1){
		currentAnimationState=0;
		time(&lastAnimationTime);
		isFilmActive=true;
		board->updateBoard2((char*) states[0].c_str());
	}
}

void XMLScene::setvsPC(bool value) {
	this->vsPc = value;
	board->updateBoard2((char*)states[0].c_str());
	pointsClicked.clear();
	pointsClickedOverTime.clear();
	gameState->setCurrentPlayer(1);
}

bool XMLScene::getvsPC() {
	return this->getvsPC();
}

string XMLScene::createPCCommand() {
	stringstream command;

	command << "comandoPC(";
	command << board->boardToString() << ",";
	command << "Points" << ",";
	command << "Tabuleiro).";

	return command.str();
}

void XMLScene::doPCMove() {
	socket->sendMessage((char*)createPCCommand().c_str());

	char *answer;
	answer = socket->receiveMessage();
	updatePointsClicked(answer);
	board->updateBoard(pointsClicked);
	gameState->setCurrentPlayer((gameState->getCurrentPlayer())%2+1);
	states.push_back(board->boardToString());
	pointsClickedOverTime.push_back(pointsClicked);
}

void XMLScene::updatePointsClicked(char* answer) {
	string coords(answer);

	pointsClicked[0] = coords[1] - '0';
	pointsClicked[1] = coords[3] - '0';
	pointsClicked[2] = coords[5] - '0';
	pointsClicked[3] = coords[7] - '0';
}

void XMLScene::setCurrentAmbient(int currentAmbient) {

	char* toMatch,*deactiveMatch,*deactiveMatch2;
	switch(currentAmbient){
	case 1:{
		toMatch =(char*) "madeira";
		deactiveMatch = (char*) "vidro";
		deactiveMatch2 = (char*) "metal";
	}
	break;
	case 2:{
		toMatch =(char*) "vidro";
		deactiveMatch = (char*) "madeira";
		deactiveMatch2 = (char*) "metal";
	}
	break;
	case 3: {
		toMatch =(char*) "metal";
		deactiveMatch = (char*) "vidro";
		deactiveMatch2 = (char*) "madeira";
	}
	break;
	}
	map<char*,Node*> temp = parser->getGraph();
	map<char*,Node*>::iterator it=temp.begin();
	for(unsigned int i=0;i<temp.size();i++,it++){
		if(strcmp(it->first,toMatch)==0){
			it->second->setActivate(true);
		}
		if(strcmp(it->first,deactiveMatch)==0) {
			it->second->setActivate(false);
		}
		if(strcmp(it->first,deactiveMatch2)==0) {
			it->second->setActivate(false);
		}
		//setNodeChildApp(it->second);
	}
}

void XMLScene::printMessage() {
	glPushMatrix();
	glTranslatef(1,5,2);
	glScalef(0.005, 0.005, 0.005);
	glColor3f(1,1,1);
	char * message;
	if(gameState->getCurrentPlayer()==1) {
		message = (char*) "Jogador 1 Venceu";
	} else {
		message = (char*) "Jogador 2 Venceu";
	}
	for(int i=0;i<16;i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN,message[i]);
	}
	glPopMatrix();
}

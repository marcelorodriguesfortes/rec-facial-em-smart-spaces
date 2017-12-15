
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

static void ler_csv(const string& filename, vector<Mat>& imagens, vector<int>& labels, char separator = ';') {
	
	ifstream file(filename.c_str(), ifstream::in);
	
	if (!file) {
		string error_message = "Entrada inválida!";
		CV_Error(CV_StsBadArg, error_message);
	}
	
	string line, path, classlabel;
	
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			imagens.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

int main() {
	string fn_haar = string("E:/Opencv-2.4.10/opencv/sources/data/haarcascades/haarcascade_frontalface_alt_tree.xml");
	string arquivo_csv = string("C:/Users/Marcelo/Documents/Visual Studio 2013/Projects/FirstOpenCV/csv.ext");

	int deviceId = atoi("0");

	// Vetores que contêm as imagens e seus respectivos ids
	vector<Mat> imagens;
	vector<int> id_imagem;

	//leitura do arquivo csv
	try {
		ler_csv(arquivo_csv, imagens, id_imagem);
	}
	catch (cv::Exception& e) {
		cerr << "Erro ao abrir o arquivo" << endl;
		exit(1);
	}
	//Obtendo o tamanho da primeira imagem para depois redimensionar as imagens para seus tamanhos originais
	int im_width = imagens[0].cols;
	int im_height = imagens[0].rows;

	// Criar um FaceRecognizer e treinar as imagens:
	Ptr<FaceRecognizer> modelo = createEigenFaceRecognizer(15, 2500.0);
	modelo->train(imagens, id_imagem);
	
	//Criando um classificador para detecção das faces
	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);

	// Obtendo um identificador do dispositivo de vídeo
	VideoCapture cap(deviceId);
	namedWindow("Reconhecimento Facial", CV_WINDOW_AUTOSIZE);

	//Caso não consiga abrir a câmera, executa esse if 
	if (!cap.isOpened()) {
		cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
		return -1;
	}
	// Vetor que contêm os retângulos dos rostos
	vector< Rect_<int> > faces;
	
	Mat frame;
	waitKey(1500);
	
	for (;;) {
		cap >> frame;
		// Clona o frame atual
		Mat original = frame.clone();

		// Converte o frame atual em escala de cinza
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);

		// Encontrando os rostos em cada frame:
		haar_cascade.detectMultiScale(gray, faces);
		// Neste ponto, você tem a posição dos rostos na variável faces.
		// Ahora obtenemos las caras, haciendo una predicción y anotación en el
		// video.
		for (int i = 0; i < faces.size(); i++) {
			// Proceso cara a cara:
			Rect face_i = faces[i];
			// Recortar la cara de la imagen. Simple con OpenCV C++:
			Mat face = gray(face_i);
			//Cambiar el tamaño de la cara es necesario para Eigenfaces y Fisherfaces:
			Mat face_redimensionada;
			cv::resize(face, face_redimensionada, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
			// Ahora se realiza la prediccion:
			int prediction = modelo->predict(face_redimensionada);
			// Y finalmente se escribe los resultados en la imagen original!
			// Primero dibujar un rectangulo rojo alrededor de la cara detectada:
			rectangle(original, face_i, CV_RGB(100, 0, 0), 1);
			// Crear el texto para la caja:

			string box_text;
			if (prediction == 2){
				box_text = format("Marcelo");

				//Enviando mensagem para o servidor
				// Initialize Winsock

				WSADATA wsaData;
				SOCKET ConnectSocket = INVALID_SOCKET;
				struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;
				char *sendbuf = "Marcelo";
				char recvbuf[DEFAULT_BUFLEN];
				int iResult;
				int recvbuflen = DEFAULT_BUFLEN;

				iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				if (iResult != 0) {
					printf("WSAStartup failed with error: %d\n", iResult);
					//return 1;
				}

				ZeroMemory(&hints, sizeof(hints));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;

				// Resolve the server address and port
				iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
				if (iResult != 0) {
					printf("getaddrinfo failed with error: %d\n", iResult);
					WSACleanup();
					//return 1;
				}

				// Attempt to connect to an address until one succeeds
				for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

					// Create a SOCKET for connecting to server
					ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
						ptr->ai_protocol);
					if (ConnectSocket == INVALID_SOCKET) {
						printf("socket failed with error: %ld\n", WSAGetLastError());
						WSACleanup();
						//return 1;
					}

					// Connect to server.
					iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
					if (iResult == SOCKET_ERROR) {
						closesocket(ConnectSocket);
						ConnectSocket = INVALID_SOCKET;
						continue;
					}
					break;
				}

				freeaddrinfo(result);

				if (ConnectSocket == INVALID_SOCKET) {
					printf("Unable to connect to server!\n");
					WSACleanup();
					//while (1);
					//return 1;
				}

				// Send an initial buffer
				iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
				if (iResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ConnectSocket);
					WSACleanup();
					//return 1;
				}

				printf("Bytes Sent: %ld\n", iResult);

				// shutdown the connection since no more data will be sent
				iResult = shutdown(ConnectSocket, SD_SEND);
				if (iResult == SOCKET_ERROR) {
					printf("shutdown failed with error: %d\n", WSAGetLastError());
					closesocket(ConnectSocket);
					WSACleanup();
					//return 1;
				}

				// Receive until the peer closes the connection
				do {

					iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
					if (iResult > 0)
						printf("Bytes received: %d\n", iResult);
					else if (iResult == 0)
						printf("Connection closed\n");
					else
						printf("recv failed with error: %d\n", WSAGetLastError());

				} while (iResult > 0);

				// cleanup
				closesocket(ConnectSocket);
				WSACleanup();




			}else
				box_text = format("Face desconhecida");

			// calcular a posição onde será escrito o texto:
			int pos_x = std::max(face_i.tl().x - 10, 0);
			int pos_y = std::max(face_i.tl().y - 10, 0);
			// colocar o texto na imagem:
			putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 0), 1.0);
		}
		// Mostrar os resultados:
		imshow("Reconhecimento Facial", original);
		// Para sair, digitar ESC:
		char key = (char)waitKey(1);
		
		if (key == 27){
			destroyAllWindows();
			break;
		}

	}
	return 0;
}

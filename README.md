# rec-facial-em-smart-space

# Descrição do sistema 

Smart spaces são sistemas de computação distribuídos, heterogêneos e pervasivos que visam
criar um ambiente interativo com sensores, aparelhos de informação e interfaces multimodais [1]. Uma
característica importante dos smart spaces é que a interação com o sistema acontece de uma forma mais
natural, onde o ambiente é capaz de reconhecer e responder à presença de indivíduos, de forma
transparente e discreta. Neste trabalho propomo-nos a realizar o reconhecimento da entrada de um
indivídio no smart space através do reconhecimento facial.

Uma das mais confiáveis e menos invasivas técnicas da biometria é o reconhecimento facial. O objetivo 
desses algoritmos é compreender como o ser humano identifica uma pessoa,
observando quais as características e objetos contidos na face. Um sistema de reconhecimento facial
eficaz deve ser capaz de identificar uma face e suas características através de uma determinada imagem,
assim como o ser humano identifica uma pessoa simplesmente olhando para uma determinada fotografia,
ou mesmo transmissão de vídeo [2]

As principais etapas (como mostrado na Figura 1) do processamento de imagens são: aquisição,
pré-processamento, segmentação e análise das imagens [3] . Na etapa de aquisição, as imagens que serão
processadas são obtidas. O pré-processamento visa melhorar a qualidade das imagens para que elas
sejam usadas nas fases posteriores. Na segmentação o objetivo é identificar regiões similares e, o
reconhecimento de imagens é a etapa onde as informações presentes nas imagens são identificadas.

<p align="center">
  <img src="https://github.com/marcelorodriguesfortes/rec-facial-em-smart-space/blob/master/Fig/Figura1.PNG" width="450"/>
</p>

Após a fase de detecção e normalização contemplamos a fase de reconhecimento de face
propriamente dito. Nesta fase avaliamos a imagem a ser reconhecida, comparando com as que estão em
um conjunto armazenado no banco de dados, através dos cálculos necessários para efetuarmos essa
comparação, acessando-as de maneira mais eficiente possível, ou seja, diminuindo a porcentagem de erro
[4]. Para métodos que reduzem o espaço de características, como o PCA, torna-se necessário a utilização
de um classificador, que tem como função, determinar valores numéricos singulares para a comparação,
verificando os valores que mais se aproximam.


Neste trabalho pretendo utilizar o método fisherfaces, também conhecido como análise de
discriminantes (LDA), que foi desenvolvido por R. A. Fisher na década de 1930. É um método específico à
classe, pois, ele trabalha com o uso de “rótulos”, isto é, uma vez identificado os rostos dizendo qual facepertence a qual pessoa, os mesmos são agrupados por pessoa, e cada agrupamento desses é conhecido
como classe. O método tenta modelar a dispersão dos pontos visando maior confiabilidade para a
classificação [5].



Portanto, o objetivo deste trabalho é utilizar o reconhecimento facial, através de imagens de
câmeras, como forma de detectar a entrada de um indivídio no ambiente inteligente. Após o
reconhecimento facial, o sistema irá configurar o ambiente de acordo com informações relacionadas a
esse indivíduo, cadastradas em um banco de dados. Um exemplo dessas configurações seria: ligar o ar-
condicionado, ligar a TV, as luzes e abrir a janela. Todas os dispositivos que compõem esse ambiente
inteligente serão simuladas por processos que rodam em uma mesma máquina. Para realização deste
trabalho será utilizada a biblioteca OpenCV para a linguagem C++. A Figura 2 mostra um esquema em alto
nível da implementação que será feita.

<p align="center">
  <img src="https://github.com/marcelorodriguesfortes/rec-facial-em-smart-space/blob/master/Fig/Figura2.PNG" width="450"/>
</p>


# Referências

[1] Singh, Ramesh, Preeti Bhargava, and Samta Kain. "State of the art smart spaces: application
models and software infrastructure." Ubiquity2006.September (2006): 7.

[2] NETO E. L. A. – Sistemas de Identificação Pessoal Utilizando Técnicas de
Reconhecimento e Verificação Facial Automáticas, 1997 .

[3] Navaux, Philippe Olivier Alexandre. Reconhecimento Automático de Padrões em Imagens
Ecocardiográficas. Diss. UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL, 2010.

[4] Tavares, Anderson Rocha, and Eloızio Cesar Drummond Salgado. "Comparaç ao de Algoritmos de
Reconhecimento de Faces em Multidoes."

[5] [BELHUMEUR1997] BELHUMEUR, P. N., HESPANHA, J. P., KRIEGMAN, D. J. “Eigenfaces vs. fisherfaces:
recognition using class specific linear projection,” IEEE Transactions on Pattern Analysis and Machine
Intelligence, vol. 19, no. 7, pp. 711-720, July 1997.

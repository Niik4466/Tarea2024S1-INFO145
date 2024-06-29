    #include "Huffman.h"
using namespace std;

vector<simboloFrec> frecuenciaGC(int* GapCodingArreglo, int largo){
    vector<simboloFrec> frecuencia;
    int j;
    for (int i = 0; i < largo; i++){
        j = 0; //iterar sobre el vector de frecuencias.
        while(j < frecuencia.size() && frecuencia[j].valor != GapCodingArreglo[i]){
            j++;
        }
        if (j == frecuencia.size())
            frecuencia.push_back({GapCodingArreglo[i], 1});
        else 
            frecuencia[j].frecuencia += 1;
    }
    //ordenamos por frecuencia de mayor a menor
    sort(frecuencia.begin(), frecuencia.end(), [](simboloFrec a, simboloFrec b){
        return a.frecuencia > b.frecuencia;
    });

    return frecuencia;
}


void imprimeFrecuencia(vector<simboloFrec> frecuencia){
    for (int i = 0; i < frecuencia.size(); i++){
        cout << "Valor: " << frecuencia[i].valor << " Frecuencia: " << frecuencia[i].frecuencia << endl;
    }
}


// todos los procesos hasta entregar los códigos de huffman canónicos
vector<simboloCod> crearCodificacionHuffman(vector<simboloFrec> frecuenciaGC){
    // declaramos la cola de prioridad

    priority_queue <simboloFrec*, vector<simboloFrec*>, CompareSimboloFrec> huffmanQueue;

    // almacenamos todas las frecuencias a la cola de prioridad

    for (int i = 0; i < frecuenciaGC.size(); ++i){
        huffmanQueue.push(&(frecuenciaGC[i]));
    }

    // creamos el árbol de huffman y obtenemos la raíz
    simboloFrec* raiz = createHuffman(huffmanQueue);
    
    // encontramos las codificaciones dado un árbol de huffman
    vector<simboloCod> codificationNormal(frecuenciaGC.size());
    for (int i = 0; i < frecuenciaGC.size(); ++i){
        codificationNormal[i].simbolo = frecuenciaGC[i].valor;
    }

    vector<bool> aux;
    codificationHuffman(raiz, codificationNormal, aux);
    return codificationNormal;
    // transforma la codificacion del árbol obtenida anteriormente a una canónica.
    vector<simboloCod> codificationCanonico(frecuenciaGC.size());
    for(int i = 0; i < frecuenciaGC.size(); ++i)
        codificationCanonico[i].simbolo = frecuenciaGC[i].valor;

    canonicHuffman(codificationNormal, codificationCanonico);

    return codificationCanonico;
}

simboloFrec* createHuffman(priority_queue <simboloFrec*, vector<simboloFrec*>, CompareSimboloFrec> &simbols){
    simboloFrec *nuevo;
    while(simbols.size() >= 2){
        nuevo = new simboloFrec();
        nuevo->izq = simbols.top();
        simbols.pop();
        nuevo->der = simbols.top();
        simbols.pop();
        nuevo->frecuencia = nuevo->izq->frecuencia + nuevo->der->frecuencia;
        simbols.push(nuevo);
    }

    nuevo = simbols.top();
    simbols.pop();
    return nuevo;
}

void codificationHuffman(simboloFrec *huffmanTree, vector<simboloCod> &codifications, vector<bool> &aux) {
    if (huffmanTree == nullptr)
        return;

    if (huffmanTree->valor != -1) { // Es una hoja del árbol
        int i = 0;
        while (i < codifications.size() && codifications[i].simbolo != huffmanTree->valor)
            i++;
        if (i < codifications.size()) // Se encontró el símbolo en el vector de codificaciones
            codifications[i].codification = aux;
        return;
    }

    aux.push_back(0);
    codificationHuffman(huffmanTree->izq, codifications, aux);
    aux.pop_back();

    aux.push_back(1);
    codificationHuffman(huffmanTree->der, codifications, aux);
    aux.pop_back();
}

/*
void codificationHuffman(simboloFrec *huffmanTree, vector<simboloCod> &codifications, vector<bool> aux){
    if (huffmanTree == nullptr)
        return;
    +
    aux.push_back(0);
    codificationHuffman(huffmanTree->izq, codifications, aux);
    aux.pop_back();
    if(huffmanTree->valor != -1){
        int i = 0;
        while(i < codifications.size() && codifications[i].simbolo == huffmanTree->valor)
            i++;
        if (codifications.size() != i)
            codifications[i].codification = aux;
    }
    aux.push_back(1);
    codificationHuffman(huffmanTree->der, codifications, aux);
}*/

void canonicHuffman(vector<simboloCod> &codifications, vector<simboloCod> &canonicCodification){

    
    int l = codifications[0].codification.size();
    vector<bool> aux = {1};

    for (int i = 0; i < l; ++i)
        canonicCodification[0].codification.push_back(0);


    for (int i = 1; i < codifications.size(); ++i){
        if (codifications[i].codification.size() == l)
            canonicCodification[i].codification = sumaBinarios(canonicCodification[i-1].codification, aux);
        else{
            l = codifications[i].codification.size();
            canonicCodification[i].codification = sumaBinarios(canonicCodification[i-1].codification, aux);
            canonicCodification[i].codification = sumaBinarios(canonicCodification[i].codification, canonicCodification[i].codification);
        }
    }
}

vector<bool> sumaBinarios(const vector<bool>& code1, const vector<bool>& code2) {
    bool carry = false;
    vector<bool> result;

    int n = code1.size();
    int m = code2.size();
    int max_size = max(n, m);

    // Ajustar el tamaño de los vectores al tamaño máximo
    vector<bool> adjusted_code1 = code1;
    vector<bool> adjusted_code2 = code2;

    if (n < max_size) {
        adjusted_code1.insert(adjusted_code1.begin(), max_size - n, 0);
    }
    if (m < max_size) {
        adjusted_code2.insert(adjusted_code2.begin(), max_size - m, 0);
    }

    for (int i = max_size - 1; i >= 0; --i) {
        bool augend = adjusted_code1[i];
        bool addend = adjusted_code2[i];

        bool sum = augend ^ addend ^ carry;
        carry = (augend && addend) || ((augend ^ addend) && carry);

        result.insert(result.begin(), sum);
    }

    if (carry) {
        result.insert(result.begin(), 1);
    }

    return result;
}

/*
Simbolo 1: Co: Char "\SO"

char ch = static_cast<char>(num);*/

/*
struct simboloCod{
    int simbolo;
    std::vector<bool> codification;
};

struct simboloCodChar{
    int simbolo;
    unsigned char representacion;
};
*/

vector<simboloCodChar> traducir(vector<simboloCod> simboloCod){
    vector<simboloCodChar> simboloCodChar(simboloCod.size());
    string binario;
    char caracter;
    int decimal;
    for (int i = 0; i < simboloCod.size(); i++){ //iteramos sobre todos los simbolos
        binario = "";
        for(int j = 0 ; j < simboloCod[i].codification.size(); j++){
            if (simboloCod[i].codification[j] == 1){           //iteramos sobre el vector de codificacion
                binario = "1" + binario;
            }
            else{
                binario = "0" + binario;
            }
        }
        simboloCodChar[i].simbolo = simboloCod[i].simbolo;
        
        //Aqui se traduce con stoi 
        decimal = stoi(binario,nullptr,2);

        
        //pasar a char 
        caracter = static_cast<unsigned char>(decimal);
        
        simboloCodChar[i].representacion = caracter;
    }
    return simboloCodChar;
}

unordered_map<unsigned char, int> CreateHash(vector<simboloCodChar> simboloCodChar){
    unordered_map<unsigned char, int> decodificar;
    for (int i = 0; i < simboloCodChar.size(); ++i){
        decodificar.insert({simboloCodChar[i].representacion, simboloCodChar[i].simbolo});
    }

    return decodificar; 
}

int busquedaBinariaSample_GCHuffman(unsigned char* GCHuffman, int* Sample, int x, int n, int m, int b, unordered_map<unsigned char, int> &decodificar) {
    int izq = 0, der = m - 1;
    if(x<Sample[0]) return -1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        if (Sample[medio] == x)
            return medio*b;
        if (Sample[medio] < x)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    
    return busquedaLinealAcotadaGCHuffman(GCHuffman, x, n, der*b, Sample[der], decodificar);
}

int busquedaLinealAcotadaGCHuffman(unsigned char* GCHuffman, int x, int n, int indice, int elemento_acotado, unordered_map<unsigned char, int> &decodificar){ 
    int elemento_sumado = elemento_acotado;
    for (int i = indice+1; i < n; ++i){
        elemento_sumado += decodificar[GCHuffman[i]];
        if (elemento_sumado > x)
            return -1;
        if (elemento_sumado == x)
            return i;
    }
    return -1;
}

unsigned char* transformarGCaGCHuffman(int* GC, vector<simboloCodChar> &simboloCodChar, int n){
    unsigned char* GCHuffman = new unsigned char[n];
    int j;
    for (int i = 0; i < n; ++i){
        j = 0;
        while (j < simboloCodChar.size() && simboloCodChar[j].simbolo != GC[i])
            j++;
        GCHuffman[i] = simboloCodChar[j].representacion;
    }
    return GCHuffman;
}
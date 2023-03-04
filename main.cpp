#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Edificio {
protected:
    int quantidadeAndares;
    // Membros privados

public:
    string endereco;
    string nome;
    // Membros públicos

    // Construtor
    Edificio(int quantidadeAndares, string endereco, string nome) {
        this->quantidadeAndares = quantidadeAndares;
        this->endereco = endereco;
        this->nome = nome;
    }

    // Getters
    int getQuantidadeAndares() {
        return quantidadeAndares;
    }

    string getEndereco() {
        return endereco;
    }

    string getNome() {
        return nome;
    }

    // Setters
    void setQuantidadeAndares(int quantidadeAndares) {
        this->quantidadeAndares = quantidadeAndares;
    }

    void setEndereco(string endereco) {
        this->endereco = endereco;
    }

    void setNome(string nome) {
        this->nome = nome;
    }
};


class ControleDeAcesso {
private:
    int quantidadeAndares;
    vector<string> tokens;

public:
    ControleDeAcesso(int quantidadeAndares) {
        this->quantidadeAndares = quantidadeAndares;
        for (int i = 0; i < quantidadeAndares; i++) {
            tokens.push_back("");
        }
    }

    bool solicitarAcesso(int andar, string token) {
        if (andar < 0 || andar >= quantidadeAndares) {
            cout << "Andar inválido!" << endl;
            return false;
        }

        if (tokens[andar] == "") {
            tokens[andar] = token;
            cout << "Acesso concedido ao andar " << andar << endl;
            return true;
        }
        else if (tokens[andar] == token) {
            cout << "Acesso concedido ao andar " << andar << endl;
            return true;
        }
        else {
            cout << "Token inválido para o andar " << andar << endl;
            return false;
        }
    }

    bool revogarAcesso(int andar) {
        if (andar < 0 || andar >= quantidadeAndares) {
            cout << "Andar inválido!" << endl;
            return false;
        }
        
        if (tokens[andar] != "") {
            tokens[andar] = "";
            cout << "Acesso revogado do andar " << andar << endl;
            return true;
        }
        else {
            cout << "Não há acesso para o andar " << andar << endl;
            return false;
        }
    }
};
    
class Empresa : public Edificio, public ControleDeAcesso {
private:
    vector<int> andaresOcupados;
    vector<string> tokens;

    string cnpj;
    string horarioFuncionamento;

public:
    // Construtor
    Empresa(int quantidadeAndares, string endereco, string nome, string cnpj, string horarioFuncionamento, vector<int> andaresOcupados)
        : Edificio(quantidadeAndares, endereco, nome), ControleDeAcesso(quantidadeAndares)
    {
        this->cnpj = cnpj;
        this->horarioFuncionamento = horarioFuncionamento;
        this->andaresOcupados = andaresOcupados;
        for (int i = 0; i < quantidadeAndares; i++) {
            if (find(andaresOcupados.begin(), andaresOcupados.end(), i) != andaresOcupados.end()) {
                tokens.push_back("");
            }
            else {
                tokens.push_back("N/A");
            }
        }
    }

    // Getters
    string getCnpj() {
        return cnpj;
    }

    string getHorarioFuncionamento() {
        return horarioFuncionamento;
    }

    vector<int> getAndaresOcupados() {
        return andaresOcupados;
    }

    // Setters
    void setCnpj(string cnpj) {
        this->cnpj = cnpj;
    }

    void setHorarioFuncionamento(string horarioFuncionamento) {
        this->horarioFuncionamento = horarioFuncionamento;
    }

    void setAndaresOcupados(vector<int> andaresOcupados) {
        this->andaresOcupados = andaresOcupados;
        tokens.clear();
        for (int i = 0; i < Edificio::quantidadeAndares; i++) {
            if (find(andaresOcupados.begin(), andaresOcupados.end(), i) != andaresOcupados.end()) {
                tokens.push_back("");
            }
            else {
                tokens.push_back("N/A");
            }
        }
    }

    // Métodos públicos
    bool solicitarAcesso(int andar, string token) {
        if (find(andaresOcupados.begin(), andaresOcupados.end(), andar) == andaresOcupados.end()) {
            cout << "Andar não ocupado pela empresa!" << endl;
            return false;
            }
            return ControleDeAcesso::solicitarAcesso(andar, token);
        }

        bool revogarAcesso(int andar) {
            if (find(andaresOcupados.begin(), andaresOcupados.end(), andar) == andaresOcupados.end()) {
                cout << "Andar não ocupado pela empresa!" << endl;
                return false;
            }
            return ControleDeAcesso::revogarAcesso(andar);
        }
    };


class Setor : public Empresa {
private:
    vector<vector<string>> tokensSalas;
    vector<string> tokensAndares;

    int quantidadeSalas;
    int andarOcupado;

public:
    // Construtor
    Setor(int quantidadeAndares, string endereco, string nome, string cnpj, string horarioFuncionamento, vector<int> andaresOcupados,
          int quantidadeSalas, int andarOcupado)
        : Empresa(quantidadeAndares, endereco, nome, cnpj, horarioFuncionamento, andaresOcupados)
    {
        this->quantidadeSalas = quantidadeSalas;
        this->andarOcupado = andarOcupado;
        for (int i = 0; i < quantidadeAndares; i++) {
            if (find(andaresOcupados.begin(), andaresOcupados.end(), i) != andaresOcupados.end()) {
                if (i == andarOcupado) {
                    tokensAndares.push_back("");
                }
                else {
                    tokensAndares.push_back("N/A");
                }
            }
            else {
                tokensAndares.push_back("N/A");
            }
        }
        tokensSalas.resize(quantidadeSalas);
        for (int i = 0; i < quantidadeSalas; i++) {
            tokensSalas[i].resize(quantidadeAndares);
            for (int j = 0; j < quantidadeAndares; j++) {
                if (j == andarOcupado) {
                    tokensSalas[i][j] = "";
                }
                else {
                    tokensSalas[i][j] = "N/A";
                }
            }
        }
    }

    // Getters
    int getQuantidadeSalas() {
        return quantidadeSalas;
    }

    int getAndarOcupado() {
        return andarOcupado;
    }

    // Setters
    void setQuantidadeSalas(int quantidadeSalas) {
        this->quantidadeSalas = quantidadeSalas;
        tokensSalas.resize(quantidadeSalas);
        for (int i = 0; i < quantidadeSalas; i++) {
            tokensSalas[i].resize(Empresa::getQuantidadeAndares());
            for (int j = 0; j < Empresa::getQuantidadeAndares(); j++) {
                if (j == andarOcupado) {
                    tokensSalas[i][j] = "";
                }
                else {
                    tokensSalas[i][j] = "N/A";
                }
            }
        }
    }

    void setAndarOcupado(int andarOcupado) {
        this->andarOcupado = andarOcupado;
        tokensAndares.clear();
        for (int i = 0; i < Empresa::getQuantidadeAndares(); i++) {
            if (find(Empresa::getAndaresOcupados().begin(), Empresa::getAndaresOcupados().end(), i) != Empresa::getAndaresOcupados().end()) {
                if (i == andarOcupado) {
                    tokensAndares.push_back("");
                }
                else {
                    tokensAndares.push_back("N/A");
                }
            }
            else {
                tokensAndares.push_back("N/A");
            }
        }
        tokensSalas.resize(quantidadeSalas);
        for (int i = 0; i < quantidadeSalas; i++) {
            tokensSalas[i].resize(Empresa::getQuantidadeAndares());
            for (int j = 0; j < Empresa::getQuantidadeAndares(); j++) {
                if (j == andarOcupado) {
                    tokensSalas[i][j] = "";
                }
                else {
                    tokensSalas[i][j] = "N/A";
                }
            }
        }
    }

    // Métodos públicos
    bool solicitarAcesso(int andar, string token) {
        if (andar == andarOcupado) {
            return Empresa::solicitarAcesso(andar, token);
        }
        else {
            cout << "Acesso negado!" << endl;
            return false;
        }
    }

    bool solicitarAcesso(int sala, int andar, string token) {
        if (sala < 0 || sala >= quantidadeSalas) {
            cout << "Sala inválida!" << endl;
            return false;
        }
        if (andar < 0 || andar >= Empresa::getQuantidadeAndares()) {
            cout << "Andar inválido!" << endl;
            return false;
        }
        if (andar == andarOcupado) {
            if (tokensSalas[sala][andar] == "") {
                tokensSalas[sala][andar] = token;
                cout << "Acesso concedido à sala " << sala << " do andar " << andar << endl;
                return true;
            }
            else if (tokensSalas[sala][andar] == token) {
                cout << "Acesso concedido à sala " << sala << " do andar " << andar << endl;
                return true;
            }
            else {
                cout << "Token inválido para a sala " << sala << " do andar " << andar << endl;
                return false;
            }
        }
        else {
            cout << "Acesso negado!" << endl;
            return false;
        }
    }

    bool revogarAcesso(int sala, int andar) {
        if (sala < 0 || sala >= quantidadeSalas) {
            cout << "Sala inválida!" << endl;
            return false;
        }
        if (andar < 0 || andar >= Empresa::getQuantidadeAndares()) {
            cout << "Andar inválido!" << endl;
            return false;
        }
        if (andar == andarOcupado) {
            if (tokensSalas[sala][andar] != "") {
                tokensSalas[sala][andar] = "";
                cout << "Acesso revogado da sala " << sala << " do andar " << andar << endl;
                return true;
            }
            else {
                cout << "Não há acesso para a sala " << sala << " do andar " << andar << endl;
                return false;
            }
        }
        else {
            cout << "Acesso negado!" << endl;
            return false;
        }
    }

    // Getters
    vector<vector<string>> getTokensSalas() {
        return tokensSalas;
    }

    vector<string> getTokensAndares() {
        return tokensAndares;
    }

        // Setters
        void setTokensSalas(vector<vector<string>> tokensSalas) {
            this->tokensSalas = tokensSalas;
        }

        void setTokensAndares(vector<string> tokensAndares) {
            this->tokensAndares = tokensAndares;
        }
    };

class Funcionario : public Setor {
private:
    string cpf;
    string tokenAndar;
    vector<string> tokensSalas;

public:
    // Construtor
    Funcionario(int quantidadeAndares, string endereco, string nome, string cnpj, string horarioFuncionamento, vector<int> andaresOcupados,
                int quantidadeSalas, int andarOcupado, string cpf, string cargo)
        : Setor(quantidadeAndares, endereco, nome, cnpj, horarioFuncionamento, andaresOcupados, quantidadeSalas, andarOcupado)
    {
        this->cpf = cpf;
        if (cargo == "Gerente" || cargo == "Diretor") {
            tokenAndar = "";
            tokensSalas.resize(quantidadeSalas);
            fill(tokensSalas.begin(), tokensSalas.end(), "");
        }
        else {
            tokenAndar = "N/A";
            tokensSalas.resize(quantidadeSalas);
            fill(tokensSalas.begin(), tokensSalas.end(), "N/A");
        }
    }

    // Métodos públicos
    bool solicitarAcesso(int sala, int andar, string token) {
        if (tokensSalas[sala] == token && (tokenAndar == "" || tokenAndar == token)) {
            return Setor::solicitarAcesso(sala, andar, token);
        }
        else {
            cout << "Acesso negado!" << endl;
            return false;
        }
    }

    void definirTokenSala(int sala, string token) {
        if (cpf == "Gerente" || cpf == "Diretor") {
            tokensSalas[sala] = token;
            cout << "Token da sala " << sala << " definido como " << token << endl;
        }
        else {
            cout << "Acesso negado!" << endl;
        }
    }

    // Getters
    string getCpf() {
        return cpf;
    }

    string getTokenAndar() {
        return tokenAndar;
    }

    vector<string> getTokensSalas() {
        return tokensSalas;
    }

    // Setters
    void setTokenAndar(string tokenAndar) {
        this->tokenAndar = tokenAndar;
    }

    void setTokensSalas(vector<string> tokensSalas) {
        this->tokensSalas = tokensSalas;
    }
};

using namespace std;

int main() {
    int opcao;
    
    // Variáveis para criar os objetos
    int quantidadeAndares, quantidadeSalas, andarOcupado;
    string endereco, nome, cnpj, horarioFuncionamento, cpf, cargo;
    vector<int> andaresOcupados;
    
    // Variáveis para armazenar informações inseridas pelo usuário
    int andar, sala;
    string token;
    
    do {
        cout << "Escolha uma opção:" << endl;
        cout << "1 - Criar um edifício" << endl;
        cout << "2 - Criar uma empresa" << endl;
        cout << "3 - Criar um setor" << endl;
        cout << "4 - Criar um funcionário" << endl;
        cout << "5 - Solicitar acesso a um andar" << endl;
        cout << "6 - Solicitar acesso a uma sala" << endl;
        cout << "7 - Definir token de uma sala" << endl;
        cout << "0 - Sair" << endl;
        cin >> opcao;
        
        switch (opcao) {
            case 1:
                cout << "Quantidade de andares: ";
                cin >> quantidadeAndares;
                cout << "Endereço: ";
                cin >> endereco;
                cout << "Nome: ";
                cin >> nome;
                Edificio edificio(quantidadeAndares, endereco, nome);
                cout << "Edifício criado com sucesso!" << endl << endl;
                break;
            case 2:
                cout << "Quantidade de andares: ";
                cin >> quantidadeAndares;
                cout << "Endereço: ";
                cin >> endereco;
                cout << "Nome: ";
                cin >> nome;
                cout << "CNPJ: ";
                cin >> cnpj;
                cout << "Horário de funcionamento: ";
                cin >> horarioFuncionamento;
                cout << "Andares ocupados (digite -1 para finalizar): ";
                while (true) {
                    int andar;
                    cin >> andar;
                    if (andar == -1) {
                        break;
                    }
                    andaresOcupados.push_back(andar);
                }
                Empresa empresa(quantidadeAndares, endereco, nome, cnpj, horarioFuncionamento, andaresOcupados);
                cout << "Empresa criada com sucesso!" << endl << endl;
                break;
        }
    }
}

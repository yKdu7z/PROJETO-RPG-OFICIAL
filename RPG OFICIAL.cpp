#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>   

using namespace std;

// Classe base
class Personagem {
protected:
    string nome;
    int vida;
    int forca;
    bool pocaoUsada;
public:
    Personagem(string n, int v, int f) : nome(n), vida(v), forca(f), pocaoUsada(false) {}

    virtual void mostrarStatus() const {
        cout <<  nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }

    virtual int atacar() {
        int dado = rand() % 10 + 1;
        int dano = forca * dado; // Calcula o dano
        cout <<  nome << " rolou um dado: " << dado << endl; // Mostra o dado rolado
        return dano; // Retorna o dano causado
    }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() const {
        return vida > 0;
    }

    void usarPocaoVida() {
        if (!pocaoUsada) {
            vida += 20; // Cura a vida
            pocaoUsada = true; //poção foi usada
            cout << nome << " usou uma pocao de cura e agora tem " << vida << " de vida." << endl;
        } else {
            cout << nome << " já usou uma pocao nesta batalha!" << endl;
        }
    }

    void usarPocaoForca() {
        if (!pocaoUsada) {
            forca += 3; // Aumenta a força
            pocaoUsada = true; // poção foi usada
            cout << nome << " usou uma poção de forca e agora tem " << forca << " de forca." << endl;
        } else {
            cout << nome << " já usou uma pocao nesta batalha!" << endl;
        }
    }

    string getNome() const { return nome; }
    int getVida() const { return vida; }
};

// Classes
class PequenoCavaleiro : public Personagem {
public:
    PequenoCavaleiro(string n) : Personagem(n, 200, 6) {}

    void mostrarStatus() const override {
        cout << "    Pequeno Cavaleiro " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class PrincesaDeHallownest : public Personagem {
public:
    PrincesaDeHallownest(string n) : Personagem(n, 200, 6) {}

    void mostrarStatus() const override {
        cout << "    Princesa de Hallownest " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class ReceptaculoPuro : public Personagem {
public:
    ReceptaculoPuro(string n) : Personagem(n, 200, 6) {}

    void mostrarStatus() const override {
        cout << "    Receptaculo Puro " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class CavaleiroDasSombras : public Personagem {
public:
    CavaleiroDasSombras(string n) : Personagem(n, 200, 5) {}

    void mostrarStatus() const override {
        cout << "    Cavaleiro das Sombras " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

// Classe para Chefes/Inimigos
class Chefe {
private:
    string nome;
    int vida;
    int forca;
public:
    Chefe(string n, int v, int f) : nome(n), vida(v), forca(f) {}

    int atacar() {
        int dado = rand() % 10 + 1;
         cout <<     nome << " rolou um dado: " << dado << endl; // Mostra o dado rolado
        return forca * dado;
    }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() const {
        return vida > 0;
    }

    string getNome() const { return nome; }
    int getVida() const { return vida; }
};

// Função para batalha
void batalha(Personagem &heroi, Chefe &inimigo) {
    cout << "   A batalha entre " << heroi.getNome() << " e o chefe " << inimigo.getNome() << " comeca!" << endl;

    while (heroi.estaVivo() && inimigo.estaVivo()) {
        char acao;
        cout << "     Escolha sua acao: (G)irar o dado para atacar, (P) usar pocao ou (F)ugir: ";
        cin >> acao;

        if (acao == 'F' || acao == 'f') {
            cout << heroi.getNome() << " fugiu da batalha!" << endl;
            return;  // Sai da função batalha se o jogador fugir
        } else if (acao == 'P' || acao == 'p') {
            char tipoPocao;
            cout << "    Escolha o tipo da pocao: (V)ida ou (F)orca: ";
            cin >> tipoPocao;

            if (tipoPocao == 'V' || tipoPocao == 'v') {
                heroi.usarPocaoVida();
            } else if (tipoPocao == 'F' || tipoPocao == 'f') {
                heroi.usarPocaoForca();
            } else {
                cout << "    Tipo de pocao invalido!" << endl;
            }
        } else if (acao == 'G' || acao == 'g') {
            // Ataque do personagem
            int danoHeroi = heroi.atacar();
            inimigo.receberDano(danoHeroi);
            cout << heroi.getNome() << " causa " << danoHeroi << " de dano ao chefe!" << endl;

            // Verifica se o chefe foi derrotado
            if (!inimigo.estaVivo()) {
                cout << inimigo.getNome() << " foi derrotado!" << endl;
                break;
            }

            // Ataque do chefe
            int danoInimigo = inimigo.atacar();
            heroi.receberDano(danoInimigo);
            cout << inimigo.getNome() << " causa " << danoInimigo << " de dano ao " << heroi.getNome() << "!" << endl;

            // Verifica se o heroi foi derrotado
            if (!heroi.estaVivo()) {
                cout << heroi.getNome() << " foi derrotado!" << endl;
                break;
            }
			
            cout << heroi.getNome() << " vida: " << heroi.getVida() << " | " << inimigo.getNome() << " vida: " << inimigo.getVida() << endl;
        } else {
            cout << "    Acao invalida! Escolha (G)irar o dado, (P) usar pocao ou (F)ugir." << endl;
        }

    }
}

//escolher uma classe de personagem
Personagem* escolherPersonagem() {
    int escolha;
    cout << " Escolha sua classe de personagem:\n";
    cout << "1. Pequeno Cavaleiro\n";
    cout << "2. Princesa de Hallownest\n";
    cout << "3. Receptaculo Puro\n";
    cout << "4. Cavaleiro das Sombras\n";
    cout << " Digite o numero correspondente a classe escolhida: ";
    cin >> escolha;

    string nome;
    cout << " Digite o nome do seu personagem: ";
    cin >> nome;

    switch (escolha) {
        case 1: return new PequenoCavaleiro(nome);
        case 2: return new PrincesaDeHallownest(nome);
        case 3: return new ReceptaculoPuro(nome);
        case 4: return new CavaleiroDasSombras(nome);
        default:
            cout << " Escolha invalida! Pequeno Cavaleiro foi selecionado por padrao.\n";
            return new PequenoCavaleiro(nome);
    }
}

void mostrarCreditos() {
    cout << "\n=========== CREDITOS ===========" << endl;
    cout << "       Desenvolvido por:" << endl;
    cout << "    1. Arthur Villas" << endl;
    cout << "    2. Bianca Medina" << endl;
    cout << "    3. Carlos Eduardo M M" << endl;
    cout << "    4. Enrico" << endl;
    cout << "================================\n" << endl;
}

int main() {
    srand(time(0));

    // Menu
    cout << "                 Bem vindo ao mundo de Hollow Knight\n\n";
    cout << "                         @@@             @@@                          \n";
    cout << "                      @@@@@                @@@@@                      \n";
    cout << "                    @@@@@                   @@@@@                    \n";
    cout << "                   @@@@                       @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                   @@@@                      @@@@                     \n";
    cout << "                    @@@@                   @@@@@                      \n";
    cout << "                      @@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "                      @@%%%%%%%%%%%%%%%%%%%%@@                        \n";
    cout << "                       @#%%%%%%%%%%%%%%%%%%%@                        \n";
    cout << "                       @#%%%%%%%%%%%%%%%%%%%@                        \n";
    cout << "                       @@@@@@@@@%%%%@@@@@@@@@                        \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                        @@@@@@@@@@@@@@@@@@@@                          \n";
    cout << "                         @@@@@@@@@@@@@@@@@@                           \n\n";

    char opcao;
    while (true) {
        cout << "            Digite (I) para Iniciar,(C) para creditos ou (S) para Sair:\n";
        cin >> opcao;

        if (opcao == 'I' || opcao == 'i') {
            // Iniciar o jogo
            cout << "\n   Em um reino subterraneo esquecido chamado Hallownest, uma antiga civilizacao se desmorona sob o peso de uma praga misteriosa. Voce, um cavaleiro destemido, desperta em meio as sombras, sem memoria de seu passado. Determinado a descobrir a verdade, voce embarca em uma jornada perigosa. Conforme avanca, voce enfrentara criaturas corrompidas, encontrara aliados inesperados e revelara os segredos do reino. O destino de Hallownest e a origem de sua propria existencia estao entrelacados em uma luta contra uma forca obscura conhecida como 'A Radiancia.' Prepare-se para desbravar os misterios de Hallownest e desafiar o que se esconde nas profundezas!\n" << endl;

            // Escolha de personagem pelo jogador
            Personagem* heroi = escolherPersonagem();
            heroi->mostrarStatus();
std::cout << "" << std::endl; // Pula para a próxima linha
            // Criação do chefe
            Chefe miniChefe("Cavaleiro Falso", 120, 3);
            //historia da encruzilhada
            
            cout << "  Quando voce esta prester a entrar no Reino de hollownest surge do ceu em seu arpao, Hornet, a princesa de Hollownest. ";
            cout << "  Hornet:  Parado ai fantasma, voce esta prestes a entrar no meu reino... quero dizer algo que um dia foi meu reino, voce nao consiguira sobreviver";
            cout << "  a Radiancia ja esta absorvendo todo esse reino... ";
            cout << "  Voce nao diz nada e so segue enfrete ignorando os avisos de Hornet ";
             std::cout << std::endl; // Linha em branco para dar um espaçamento
			cout << "  Apos voce entrar em Hallownest, a primeira cidade que ele se depara ";
     		cout << "e a Encruzilhada Esquecida. Um lugar sombrio e desolado, cheio de vida e energia, ";
     		cout << "mas agora apenas ecos de uma gloria esquecida permanecem.\n";
     		cout << "As construcoes antigas e o silencio opressivo sao quebrados apenas pelo som distante ";
     		cout << "de criaturas vagando nas sombras.\n";
     		cout << "  Enquanto explora as ruinas, voce sente que algo nao esta certo. ";
     		cout << "Uma sensacao de vazio se mistura a tensao no ar, como se o proprio reino estivesse ";
      		cout << "tentando esconder seus segredos. A poeira e o brilho espectral de pequenos insetos ";
     		cout << "iluminam o caminho, guiando o personagem por corredores abandonados e pontes precarias.\n";
     		cout << "  Logo, voce comeca a encontrar sinais de resistencia: pequenas marcas de batalha nas paredes ";
     		cout << "e armadilhas deixadas por antigos guerreiros. Cada passo o leva mais fundo nas encruzilhadas, ";
     		cout << "ate que ele escuta um som perturbador e uma respiracao pesada de uma criatura colossal.\n";
     		cout << "Avancando com cautela, ele chega a um salao amplo, onde um antigo guerreiro caido, conhecido como ";
     		cout << "Cavaleiro Falso, permanece em guarda, como se estivesse esperando por intrusos.\n";
     		cout << "  O Cavaleiro Falso, uma figura grotesca e intimidadora, bloqueia o caminho. Sua armadura pesada ";
     		cout << "reflete a luz fraca, e seus olhos brilham com uma ferocidade sombria. Para seguir adiante e desvendar ";
     		cout << "os segredos de Hallownest, voce sabe que deve enfrentar essa ameaca imponente.";
     			  std::cout << std::endl; // Linha em branco para dar um espaçamento
            // Opção de combate com o chefe
            char escolha;
            cout << "              		    @     @                        \n";
    	cout << "              		   @@     @@                        \n";
    cout << "                        @@@      @@@                            \n";
    cout << "                      @@@@        @@                            \n";
    cout << "              @@      @@@         @@@          @@@@@@          \n";
    cout << "    @@@@@@@@@@@@@@   @@@@@      @@@@@        @@@@@@@@@@@       \n";
    cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@      \n";
    cout << "          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@  @@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@@  @@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@@@  @@@@@  @@@@@@@@@@@@@@@@@@@@@@@@       \n";
    cout << "           @@@@@@@@@@@@@ @@@@ @@@@@@@@@@@@@@@@@@@@@@@@@        \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@  @@@                   \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "               @@@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "               @@@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "              @@@@                @@@@@@@                       \n";
    cout << "               @@@                   @@@@@                      \n";
    cout << "                                       @@                     \n";
            cout << "\n            Voce encontrou um chefe, o Cavaleiro Falso! Deseja batalhar? (B para batalha, F para fugir): ";
            cin >> escolha;

            if (escolha == 'B' || escolha == 'b') {
                batalha(*heroi, miniChefe);
            } else {
                cout << heroi->getNome() << " decidiu nao batalhar com Cavaleiro Falso e Fracassou na sua missao de trazer a paz para Hollownest." << endl;
            }
             
		     // Criação do segundo chefe
        Chefe miniChefe2("Mestre Das Almas", 100, 4);
        std::cout << std::endl;
        std::cout << "Apos derrotar o Cavaleiro Falso voce adquiriu o Brasao Das Almas, com isso voce desbloqueou a passagem para o Santuario das almas." << std::endl;
    	std::cout << "A caminho do santuario das almas voce sente que algo esta te observando, chegando ao topo do santuario voce ve uma estatua parecida com voce, mas tem algo diferente..." << std::endl;
    	std::cout << std::endl; // Linha em branco para dar um espaçamento
    	std::cout << "\"Surge das sombras o Mestre Das Almas\"" << std::endl;
        
    cout << "                            @@          @@                      \n";
    cout << "                         @@%#%@ @@@@@@@@@%%@                    \n";
    cout << "                        @%####%+.-+..:*:-%##@@                  \n";
    cout << "                      @@##@@@@+++=+*#*#-@@@@%%%@                \n";
    cout << "                     @%#@-----@+*======@-===@*#%@@               \n";
    cout << "                @@ @@##@-----=@=========@---@-#%@@              \n";
    cout << "               @%%@@###=@@@@@+=+*********@@@@=%%@%##@          \n";
    cout << "               @####%%=====+#*==============##*+%%%%@          \n";
    cout << "               @%##***#%*#*===================+#%#*@@          \n";
    cout << "               @###******####*+======#*+**===+##***@@          \n";
    cout << "             @@####*************#%@%%:.::=%%#*******%@         \n";
    cout << "              @##%##****************%-.::=%*********##@        \n";
    cout << "              @@@@@@%%%%*************%*-+%******######%@       \n";
    cout << "              @@%%#%%#@@@@%@@@@*###%@#*%#*#@@@@@@%%%%@@        \n";
    cout << "            @@%%%@%%#%%##%%#####%#*%#**%#*%#@###%@#%@%%%@@     \n";
    cout << "         @@@%%%@%%%%%@##%%####%%****#%*@#%**#%###%%%%%@%%%@    \n";
    cout << "    @@@%%%%%%@%%%%%%%%%@%##%@%@******#@@%***#%@%%%%@%%%@@%%@   \n";
    cout << "    @@@%%%%@%%%%%%@%%%@%%%%%#%#*******%#*##%%%@@%%%%@%%%%@%%@  \n";
    cout << " @@@%@@%%%@%%%%%@%%%%@%%%%%####%%#####%##%%#@%#%@%%%%%@%%%%@@  \n";
    cout << "@@@     @@@@@%@@%%%%%%%%%@%######%%%%@%%##%%@%%%@@%%%%%@%%%%@@ \n";
    cout << "         @ @@@@@@%%@%%%%%%%#@@%####%%#%@@%##@%%%%@%%%%@@@%%%%@@\n";
    cout << "             @@%@@@%%%%%@%%#@@#%%%%%%@##%%#%%##%%@%%%%@@ @@@@%@\n";
    cout << "            @@@@ @@%%%%%@%%@%@%%@@%%@@#%@%#%@@%@ @@%%%@@ @@  @@\n";
    cout << "           @@@    @  @%@@%@@@#@%@@%@@#@@@@@@@@@  @%%%@@@     @@\n";
    cout << "            @        @%@@@  @%%%%@@@#@@@#@@      @%%%@         \n";
    cout << "                      @@@   @@#@#@@%@ @%@@       @%@@@@        \n";
    cout << "                       @@    @@@%@@%@ @@         @@@           \n";
    cout << "                             @@ @@@@@ @@          @@@          \n";
    cout << "                                @                   @          \n";
    	std::cout << "" << std::endl;
        cout << "\nVoce encontrou o Mestre Das Almas! Deseja batalhar? (B para batalha, F para fugir): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe2);
        } else {
            cout << heroi->getNome() << " decidiu nao batalhar com o Mestre Das Almas e Fracassou na sua missao de trazer a paz para Hollownest." << endl;
        }
    	 
    Chefe miniChefe3("Defensor Do Esterco", 100, 5);
    std::cout << std::endl; // Linha em branco para dar um espaçamento
    std::cout << "Parabens pela sua vitoria grandiosa...\n";
std::cout << "Apos ter derrotado o Cavaleiro Falso e o Mestre Das Almas e possivel ouvir um rugido alto que vem do alem.\n";
std::cout << "Com a derrota do Mestre Das Almas voce conseguiu um mapa e descobre que esse rugido misterioso vem do Templo do Ovo Negro, onde esta escondido a radiancia...\n\n";
std::cout << std::endl; // Linha em branco para dar um espaçamento
std::cout << "Mas para chegar la voce deve passar pela Hidrovia Real...\n";
std::cout << "A caminho da Hidrovia voce ouve um som barulhento como se alguem estivesse batendo em seu peito e gritando, voce vai investigar....\n\n";
std::cout << "\"Surge do CHAO coberto de esterco, o Defensor Do Esterco\"\n";
std::cout << std::endl; // Linha em branco para dar um espaçamento
    cout << "                       @@   @@            \n";    
    cout << "                     @@%@   @@@            \n";
    cout << "                   @%%@      @%@           \n";
    cout << "                  @%%@@     @@%%@          \n";
    cout << "                 @%#@@       @%#@          \n";
    cout << "                  @%@@%%%@@@@%#%@          \n";
    cout << "        @@@       @*=%###=#%%@@@           \n";
    cout << "     @%%###%@   @@%######%%%#%             \n";
    cout << "  @@@%#%%@@%%@@@@%%%%######%*#@            \n";
    cout << " @#%###@%%@%@#++%%####*++#@%+%@@@@@@       \n";
    cout << "@@%#@%**%@%*#%@@%%%%%%@%%#%%@@%*++++*#@    \n";
    cout << "@%%@%##%%++##%%######%%%@@@%##%@%%%%#*+*@  \n";
    cout << "@#%%%%%%+*##%@########%%##%@%%%#%@@%###*%@@\n";
    cout << " @%+#%%+*##%@################%@%%###%@%#+*@\n";
    cout << "   @%%%%%%@@%%@@@@@@@%%%#########%%%@%#%#+%\n";
    cout << "     @+####%%%########%%%@%%######@##@@%%*@\n";
    cout << "    @#+####%%##############%@%%###@@@@@#+@ \n";
    cout << "     @*####%%#################%@+%##*+*%@  \n";
    cout << "     @+####%%##################*%@@@@@     \n";
    cout << "      @*###%%#################**@          \n";
    cout << "       @%%@@@%%@@@@@@@@%%%###+#@           \n";
    cout << "      @##@%##@%############@%@             \n";
    cout << "      @+#%@@@@@@%#######%@@#+%@            \n";
    cout << "      @*##%@########%@@%####*+%@           \n";
    cout << "      @#%%@@@@@@@@%%@%@@@%%%#**@           \n";
    cout << "     @@*%@                  @@@*@@         \n";
    cout << "     @+#@                    @@%*#@        \n";
    cout << "     @+@@                      @@*@        \n";
    cout << "    @%@@                         %%@       \n";
    cout << "   @@                            @@@       \n";
    	std::cout << "" << std::endl; 
        cout << "\nVoce encontrou o Defensor Do Esterco! Deseja batalhar? (B para batalha, F para fugir): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe3);
        } else {
            cout << heroi->getNome() << " decidiu nao batalhar com o Defensor Do Esterco e seguiu em frente." << endl;
        }
        
    std::cout << "" << std::endl;
        Chefe miniChefe4("O Cavaleiro Vazio", 100, 5);
        std::cout << "Voce esta no caminho certo...\n";
std::cout << "Apos derrotar o Defensor Do Esterco voce ja esta pronto para ir ao Templo Do Ovo Negro\n";
std::cout << "e derrotar a radiancia para trazer a paz de Hallownest.\n\n";

std::cout << "Chegando ao Templo Do Ovo Negro se encontra na porta hornet...\n";
std::cout << "Hornet: Parabens fantasma por ter derrotado os aliados da radiancia, ainda mais por tirar todo aquele esterco do esgoto hahaha!\n";
std::cout << "Voce segue concentrado em sua missao e vai entrar no Templo.\n";
std::cout << "Hornet: Eu ate queria te ajudar nessa sua ultima missao, mas eu preciso resolver outros assuntos em Silksong. Conto com voce, fantasma.\n\n";

std::cout << "Voce entra no templo e la esta uma luz no fim do tunel, so que parece tudo facil demais...\n\n";

std::cout << "\"Barulhos de correntes se rompendo no ceu do templo\"\n";

    	std::cout << "                            @                            \n";
std::cout << "                          @@                              \n";
std::cout << "                        @@@                               \n";
std::cout << "                      @@@@                                \n";
std::cout << "                     @@@                                 \n";
std::cout << "                   @@@                                    \n";
std::cout << "                 @@@@                 @@@                \n";
std::cout << "                @@@@                 @%@@      @@        \n";
std::cout << "              @@@@                 @@%@@       @@        \n";
std::cout << "             @@@@                  @%@@        @@        \n";
std::cout << "           @@@@                  @@%%@@       @%@        \n";
std::cout << "        @@@@@@            @@@@@@@@%%%%@     @@@%@        \n";
std::cout << "       @@@@@   @@@@@  @@@@@@@@@@@@%%%@@@@   @%%%@        \n";
std::cout << "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%@@@@@@@ @%%@         \n";
std::cout << "     @@@@@@@       @@@@@@@@@@@@@@%%%@@@@@@@@%%%@         \n";
std::cout << "    @@@@           @@@@@@@@@@@@@@%%%%@@@@@@@%%@@         \n";
std::cout << "  @@@              @@@@@@@@@@@@@@%%%%@@@@@%%%%@          \n";
std::cout << " @@@              @@@@@@@@@@@@@@@%%%%@@@@@%%%@           \n";
std::cout << "@@                @@@@@@@@@@@@@@@%%%%@@@@%%%@@@          \n";
std::cout << "                 @@@@@@@@@@@@@@@@@%%%%@@%%%@@@@@         \n";
std::cout << "                   @@@@@@@@@@@@@@@@@%@@%%@@@@@@@@@@@     \n";
std::cout << "                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     \n";
std::cout << "                       @ @@@@@@@@@@@@@@@@@@@@@@@@@@@@    \n";
std::cout << "                           @@@@@@      @@@@@@@@@@@@@@@@  \n";
std::cout << "                          @@@@@@@@@@@@@@@@@@@@@@@@@@     \n";
std::cout << "                        @@@@@@@@@@@@  @@@@@@@@@@@@@@@    \n";
std::cout << "                      @@@@@@@        @@@@@@   @@@@@@@    \n";
std::cout << "                    @@@@@          @@@@         @@@@@@@  \n";
std::cout << "                   @@@@           @@@              @@@@@@\n";
std::cout << "                   @@@           @@@                     \n";
std::cout << "                   @@@           @@                      \n";
std::cout << "                  @@@                                      \n";
std::cout << "                  @@@                                      \n";
std::cout << "                  @@@                                      \n";
std::cout << "                   @@                                      \n";
std::cout << "                   @@                                      \n";
std::cout << "                    @                                      \n";

    	std::cout << "" << std::endl; 
        cout << "\nVoce encontrou o Caveleiro Vazio, O protetor da radiancia ! Deseja batalhar? (B para batalha, F para fugir): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe4);
        } else {
            cout << heroi->getNome() << " decidiu nao batalhar com o Cavaleiro vazio e Fracassou na sua missao de trazer a paz para Hollownest." << endl;
        }
        
    std::cout << "" << std::endl;
    Chefe miniChefe5("Radiancia", 100, 5);
    std::cout << "Apos ter essa batalha lendaria contra o Cavaleiro Vazio, voce entende de quem era aquela estatua no Santuario das Almas que se parece com voce,\n";
std::cout << "pois voce e o Cavaleiro Vazio sao receptaculos e irmaos criados pelo Rei Palido para tentar derrotar a Radiancia...\n\n";

std::cout << "Agora voce tem a opcao de salvar Hallownest ou salvar seu irmao da Radiancia.\n";

    	std::cout << "                            @                             " << std::endl;
    std::cout << "                            %                             " << std::endl;
    std::cout << "         @@  @@            @%               @@           " << std::endl;
    std::cout << "        @@@ @@@            @%@              @@@    @     " << std::endl;
    std::cout << "       @@@@@@@@     @      @%@      @       @@@@  @@@    " << std::endl;
    std::cout << "       @@@@@@@      @@     @%@     @@       @@@@  @@@    " << std::endl;
    std::cout << "       @@@@@@@@     @@     @%@     @@       @@@@  @@@    " << std::endl;
    std::cout << "       @@@@@@@@      %@    @%@    @%        @@@@ @@@@    " << std::endl;
    std::cout << "@@     @@@@@@@@      @%@   @%@   @%@        @@@@@@@@@   @" << std::endl;
    std::cout << "@@     @@@@@@@@@      @@   %%@   @@        @@@@@@@@@@  @@" << std::endl;
    std::cout << "@@@    @@@@@@@@@@     @%@  @%%  @%@       @@@@@@@@@@   @@" << std::endl;
    std::cout << "@@@@   @@@@@@@@@@@    @@%@@@@@@@%@@      @@@@@@@@@@@ @@@@" << std::endl;
    std::cout << "@@@@@@ @@@@@@@@%@%@@@ @@@@ @@@ @@@    @@@@@@@@@@@@@ @@@@@" << std::endl;
    std::cout << " @@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@%@%@@@@@@@@@@@ @@@@@ " << std::endl;
    std::cout << "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  " << std::endl;
    std::cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;
    std::cout << "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@%%%@%%%@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << " @@@@@@@@@@@@@@@@@@@@@@@@@%%%@%%@%@@@@@@@@@@@@@@@@@@@@@@ " << std::endl;
    std::cout << "   @@@@@@@@@@@@@@@@@@@@@%%%@@@%%%%@@@@@@@@@@@@@@@@@@@@@  " << std::endl;
    std::cout << "      @@@@@@@@@@@@@@@@@@@%%@@@%%@@@@@@@@@@@@@@@@@@@@@    " << std::endl;
    std::cout << "         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       " << std::endl;
    std::cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@              " << std::endl;
    std::cout << "                     @@@@@@@@@@@@@@@@                    " << std::endl;
    std::cout << "                       @@@@@@@@@@@@                      " << std::endl;
    std::cout << "                         %@@@@@%                         " << std::endl;
    std::cout << "                        @@@@@@@%@                        " << std::endl;
    std::cout << "                        @@@@@@@@@                        " << std::endl;
    std::cout << "                       @@@@@@@@@@@                       " << std::endl;
    std::cout << "                        @@@@@@@@@@                       " << std::endl;
    std::cout << "                        @@%%@%%@%@                       " << std::endl;
    std::cout << "                       @@@%%@@%@@@                       " << std::endl;
    std::cout << "                        @@@@ %%@@@                       " << std::endl;
    std::cout << "                        @%@@ @%@%                        " << std::endl;
    std::cout << "                        @%@@ %@%@                        " << std::endl;
    std::cout << "                        %%@%@@@%@                        " << std::endl;
    std::cout << "                        @@%%@%@%%                        " << std::endl;
    std::cout << "                         %%@@%%%@                        " << std::endl;
    std::cout << "                         @%@@%%@                         " << std::endl;
    std::cout << "                          @@@@%@                         " << std::endl;
    std::cout << "                          @%@@@                          " << std::endl;
    std::cout << "                          @@@%@                          " << std::endl;
    std::cout << "                          @%@%%                          " << std::endl;
    std::cout << "                           @@%@                          " << std::endl;
    std::cout << "                           %@@@                          " << std::endl;
    std::cout << "                           @@@                           " << std::endl;
    	std::cout << "" << std::endl; 
        cout << "\nVoce encontrou a Radiancia ! O que deseja fazer? (B para salvar hallownest, F para salvar seu irmao): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe5);
            cout << "\n com a derrota da radiancia voce conseguiu restaurar a paz em hollownest, Hornet e todos os cidadoes de hollownest agradecem a sua bravura pequeno fantasma!" << endl;
            
            cout << "                                FIM DE JOGO" << endl;
            std::cout << "                       OBRIGADO POR JOGAR NOSSO JOGO!                                                            \n";
            
     		cout << "                    =========== CREDITOS ===========" << endl;
     		cout << "                            Desenvolvido por:" << endl;
     		cout << "                      1. Arthur Villas" << endl;
     		cout << "                      2. Bianca Medina" << endl;
     		cout << "                      3. Carlos Eduardo M M" << endl;
    		cout << "                      4. Enrico" << endl;
     		cout << "                   ================================\n" << endl;
        } else {
            cout << heroi->getNome() << " decidiu salvar seu irmao, voce assume a responsabilidade de prisionar a radiancia dentro de voce mesmo com vc preso." << endl;
            std::cout << "          %                                                                                                \n";
std::cout << "         %%%                                                                                               \n";
std::cout << "         %#*%                                                                                              \n";
std::cout << "         %*+%                                                                                              \n";
std::cout << "        %#+*%                                                                                              \n";
std::cout << "       %#++#%                                                                                              \n";
std::cout << "      %#+++%%         %%%%                                                                                 \n";
std::cout << "     %#+++#%       %%#*%%                                                                                  \n";
std::cout << "    %#+++#%      %%#+#%                                                                                    \n";
std::cout << "   %#+++*%%     %%*+*%                                                                                     \n";
std::cout << "  %%++++%%     %%++*%                                                                                      \n";
std::cout << " %%*+++#%      %+++#%                                                                                      \n";
std::cout << " %#++++%%     %#+++#%                                                                                      \n";
std::cout << "%%*+++*%%     %#+++#%                                                                                      \n";
std::cout << "%#+++++%%     %#++++%%                                                                                     \n";
std::cout << "%#+++++*%%     %*+++*%%                                                                                    \n";
std::cout << "%%*++++++#%     %*++++%%                                                                                   \n";
std::cout << " %%+++++++*%%%   %#++++*#%%%    %%%%%    %                                                                 \n";
std::cout << "  %%+++++++++*#%%%%#+++++++#%%%#++++*####*%%                                                               \n";
std::cout << "    %*++++++++++++++++++++++*#++++++++++++*%                                                               \n";
std::cout << "     %%#*+++++++++++++++++#*++#%%%#%*++++++#%                                                              \n";
std::cout << "        %%%#+++++++++++*##*++#%%#***#*+++++*%%                                                             \n";
std::cout << "            %%%*+++++++#*++++#%#*****#*+++++#%                                                             \n";
std::cout << "               %#++++*#*+++++#%%*****##+++++#%                                                             \n";
std::cout << "                %#++%%#%*+++++%%#*****#+++++#%                                                             \n";
std::cout << "                %%**%%#*##+++++%%#***##+++++%%                                                             \n";
std::cout << "                 %#+#%%**#*+++++#%%%#*+++++#%                                                              \n";
std::cout << "                  %#+%%#*##+++++++++++++++#%%%%             %%%%%%%%%%%%%%%%%%                             \n";
std::cout << "                  %%**%%###++++++++++++++#%####%%%%%%%%%%%%####################%%%%            %%         \n";
std::cout << "                 %%%%*+#%%+++++++++++++#%%##########%%%%%%%%%%%###############%%####%%%%      %%%         \n";
std::cout << "                 %%%%%%*++++++++++++*#%%####%%%%####################%%%%%%%%%#######%#####%%%##%%         \n";
std::cout << "                  %%%%%%%%%#####%%%%%%###%%#######################################%%%####%%##%%           \n";
std::cout << "                    %%%%%%%%%%%%%%%######%%%%%%%%%####################%%###########%%%%%%%########%       \n";
std::cout << "                        %%%%%%%%%%%%%%########################################################%%%%%%%%%%  \n";
std::cout << "                                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#####%%%%%%%%%%%%%%%%%%%%%%%  \n";
std::cout << "" << std::endl;
std::cout << "                               FIM DE JOGO                                                              \n";
std::cout << "                      OBRIGADO POR JOGAR NOSSO JOGO!                                                            \n";
     cout << "                    =========== CREDITOS ===========" << endl;
     cout << "                            Desenvolvido por:" << endl;
     cout << "                      1. Arthur Villas" << endl;
     cout << "                      2. Bianca Medina" << endl;
     cout << "                      3. Carlos Eduardo M M" << endl;
     cout << "                      4. Enrico" << endl;
     cout << "                   ================================" << endl;
        }
        
            delete heroi;
            break;
        } else if (opcao == 'C' || opcao == 'c') {
            mostrarCreditos();
        } else if (opcao == 'S' || opcao == 's') {
            cout << "\nObrigado por jogar Hollow Knight! Ate a proxima!" << endl;
            break; // Sai do loop
        } else {
            cout << "\nOpcao invalida! Tente novamente.\n" << endl;
        }
    }

    return 0;
}
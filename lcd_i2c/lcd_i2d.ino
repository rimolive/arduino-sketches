#define pinBRILHO 5    //Define como 5 a palavra pinBRILHO
#define pinCONTRASTE 9 //Define como 9 a palavra pinCONTRASTE
#define pinRELE 7      //Define como 7 a palavra pinRELE
#include <Wire.h> //Inclui a biblioteca Wire.h para se utilizar a comunicação I2C
#include <LiquidCrystal_I2C.h> //Inclui a biblioteca LiquidCrystal_I2C.h
                              //para se fazer comunicação I2C com o display LCD

LiquidCrystal_I2C lcd(32,16,2); //Inicia o LCD com os parâmetros (Endereço I2C, Colunas, Linhas)
int botoes; //Variável para a leitura dos botões
int i; //Variável para contagem
int menu_cont; //Variável para contagem dos menus
int sel=0; //Variável para verificar estado do botão selecionar
int estadoRELE=0; //Variável para alteração do estado do Relé (Relé DESLIGADO)
float pwm_brilho = 255; //Variável para controle de pwm do brilho
float pwm_contraste = 0; //Variável para controle de pwm do contraste
float brilho_porcent; //Variável para conversão do pwm do brilho em porcentagem (255 = 100%)
float contraste_porcent; //Variável para conversão do pwm do contraste em porcentagem (255 = 100%)
void setup()
{
  Serial.begin(9600); //Inicia a Serial para se utilizar o Serial Monitor
lcd.init(); //Comando para inicialização do Display LCD
  lcd.backlight(); //Comando para inicialização do Display LCD
pinMode(pinBRILHO,OUTPUT); //Configura como saída o pino 5 (pinBRILHO)
  pinMode(pinCONTRASTE,OUTPUT); //Configura como saída o pino 9 (pinCONTRASTE)
pinMode(pinRELE,OUTPUT); //Configura como saída o pino 7
  digitalWrite(pinRELE,estadoRELE); //Relé = DESLIGADO (estadoRELE=0);
inicializacao(); //Executa a função da tela de início
}
void loop()
{
  botoes=analogRead(A0); //Faz a leitura analógica do pino A0 e guarda na variável botoes
  Serial.println(botoes); //Escreve no Serial Monitor o valor ligo pelo pino A0
  delay(100); //Delay de 100 milissegundos
  atualiza_menu();        //Executa a função para atualizar o menu
}
//===========================INICIALIZA A TELA DA DEMONSTRAÇÃO===========================
void inicializacao() //Função de inicialização da tela LCD para a aplicação
{
  analogWrite(pinBRILHO,255); //Inicializa o brilho no máximo (255 = 100%)
  brilho_porcent = (pwm_brilho/255) * 100;
  analogWrite(pinCONTRASTE,0); //Inicializa o contraste no mínimo (0 = 0%)
  contraste_porcent = (pwm_contraste/255) * 100;
Serial.println(""); //Pula uma linha
  Serial.println("LCD SHIELD I2C: INICIADO" ); //Escreve no Serial Monitor
lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna da primeira linha
  lcd.print(" LCD Shield I2C"); //Escreve no LCD
for(i=0;i<=4;i++) //Laço para a o efeito de piscagem da segunda linha
  {
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("                "); //Limpa segunda linha
    delay(250); //Permanece por 250 milissegundos apagada
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("labdegaragem.com"); //Escreve na tela do LCD a mensagem "labdegaragem.com"
    delay(250); //Permanece por 250 milissegundo acesa
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++ATUALIZAÇÃO DA LISTA DOS MENUS==================
void atualiza_menu()
{
  if(botoes > 100 && botoes < 200) //Se botão da esquerda for pressionado
  {
    menu_cont--; //Volta para o MENU anterior
  }
else if(botoes > 700 && botoes < 800) //Senão se o botão da direita for pressionado
  {
    menu_cont++;  //Vai para o próximo MENU
  }
  else if(botoes < 100)
  {
    sel = 1; //Valida que o botão de seleção foi pressionado
  }
  trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
  menu_list(); //Vai para a lista de MENU
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//===============================================LISTA DOS MENUS=========================
void menu_list()
{

  if(menu_cont == 0) //Menu 1: Tela de Início
  {
    lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna da primeira linha
    lcd.print(" LCD Shield I2C "); //Escreve no LCD
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("labdegaragem.com"); //Escreve na tela do LCD a mensagem "labdegaragem.com"
  }
else if(menu_cont == 1) //Menu 2: Tela de Ajuste do Brilho
  {
    lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna da primeira linha
    lcd.print("AJUSTE BRILHO   "); //Escreve no LCD
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("                "); //Escreve na tela do LCD a mensagem "labdegaragem.com"
    if(sel == 1) //Se botão de seleção for pressionado
    {
      while(sel == 1) //Enquanto o botão de selecionar não for pressionado denovo
      {
        botoes=analogRead(A0); //Lê os botões
        ajuste1(); //Vai para a função de ajuste do Brilho
        lcd.clear(); //Limpa LCD
        lcd.print("BRILHO = "); //Escreve no Serial Monitor "BRILHO =", sem pular linha
        lcd.print(brilho_porcent); //Escreve no Serial Monitor o valor em porcentagem do brilho
        lcd.print("%"); //Escreve no Serial Monitor "%" e pula linha
        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
        if(botoes < 100) //Se o botão de seleção for pressionado
        {
          sel = 0; //Sai do MENU
          trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        }
}
    }
  }
else if(menu_cont == 2)//Menu 3: Tela de Ajuste do Contraste
  {
    lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna da primeira linha
    lcd.print("AJUSTE CONTRASTE"); //Escreve no LCD
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("                ");
    if(sel == 1) //Se botão de seleção for pressionado
    {
      while(sel == 1) //Enquanto o botão de selecionar não for pressionado denovo
      {
        botoes=analogRead(A0); //Lê os botões
        ajuste2();  //Vai para a função de ajuste do Brilho
        lcd.clear(); //Limpa LCD
        lcd.print("CONTRASTE = "); //Escreve no Serial Monitor "BRILHO =", sem pular linha
        lcd.print(contraste_porcent); //Escreve no Serial Monitor o valor em porcentagem do brilho
        lcd.print("%"); //Escreve no Serial Monitor "%" e pula linha
        trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
        if(botoes < 100) //Se o botão de seleção for pressionado
        {
          sel = 0; //Sai do MENU
          trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        }
      }
    }
  }
else if(menu_cont == 3)//Menu 4: Tela de Estado do Relé
  {
    lcd.setCursor(0,0); //Posiciona o cursor na primeira coluna da primeira linha
    lcd.print("ESTADO DO RELE  "); //Escreve no LCD
    lcd.setCursor(0,1); //Posiciona cursor
    lcd.print("                ");
    if(sel == 1) //Se botão da esquerda for pressionado
    {
      while(sel == 1)
      {
        botoes=analogRead(A0); //Lê os botões
        lcd.clear(); //Limpa LCD
        lcd.print("ESTADO = "); //Escreve no Serial Monitor "BRILHO =", sem pular linha
if(estadoRELE == 0) //Se o relé estiver desacionado
        {
          lcd.setCursor(9,0); //Posiciona CURSOR
          lcd.print("OFF"); //Escreve OFF no LCD
        }
else if(estadoRELE == 1) //Se o relé estiver acionado
        {
          lcd.setCursor(9,0); //Posiciona CURSOR
          lcd.print("ON"); //Escreve ON no LCD
        }
trata_botao2(); //Chama a função para tratamento do botão para executar somente quando for clicado
        ajuste3();
        if(botoes < 100) //Se o botão de seleção for pressionado
        {
          sel = 0; //Sai do MENU
          trata_botao(); //Chama a função para tratamento do botão para executar somente quando for clicado
        }
      }
    }
  }
else if(menu_cont == 4) //Se a contagem de menu for para 4
  {
    menu_cont = 0; //Volta para o primeiro menu
  }
  else if(menu_cont == -1) //Se a contagem de menu for para -1
  {
    menu_cont = 3; //Volta para o último menu
  }
}
//---------------------------------------------------------------------------
//============================AJUSTES DOS MENUS================================
void ajuste1()
{
  if(botoes > 100 && botoes < 200) //Se botão da esquerda for pressionado
  {
    if(pwm_brilho > 0) //Se o PWM do brilho estiver maior que 0
    {
      pwm_brilho -= 25.5; //Subtrai 25.5(10%) no PWM do brilho
      analogWrite(pinBRILHO,pwm_brilho); //Atualiza o PWM do brilho
    }
brilho_porcent = (pwm_brilho/255) * 100; //Guarda na variável brilho_porcente
    //o valor do PWM convertido em porcentagem
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
else if(botoes > 700 && botoes < 800) //Senão se o botão da direita for pressionado
  {
    if(pwm_brilho < 255) //Se o PWM do brilho estiver menor que 255
    {
      pwm_brilho += 25.5; //Soma 25.5(10%) no PWM do brilho
      analogWrite(pinBRILHO,pwm_brilho); //Atualiza o PWM do brilho
    }
brilho_porcent = (pwm_brilho/255) * 100; //Guarda na variável brilho_porcente
    //o valor do PWM convertido em porcentagem
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
}
void ajuste2()
{
  if(botoes > 200 && botoes < 300) //Senão se o botão de baixo for pressionado
  {
    if(pwm_contraste > 0) //Se o PWM do contraste estiver maior que 0
    {
      pwm_contraste -= 25.5; //Subtrai 25.5(10%) no PWM do contraste
      analogWrite(pinCONTRASTE,pwm_contraste); //Atualiza o PWM do contraste
    }
contraste_porcent = (pwm_contraste/255) * 100; //Guarda na variável contraste_porcente
    //o valor do PWM convertido em porcentagem
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
else if(botoes > 400 && botoes < 500) //Senão se o botão de cima for pressionado
  {
    if(pwm_contraste < 255) //Se o PWM do contraste estiver menor que 255
    {
      pwm_contraste += 25.5; //Soma 25.5(10%) no PWM do contraste
      analogWrite(pinCONTRASTE,pwm_contraste); //Atualiza o PWM do contraste
    }
contraste_porcent = (pwm_contraste/255) * 100; //Guarda na variável contraste_porcente
    //o valor do PWM convertido em porcentagem
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
}
void ajuste3()
{
  if(botoes > 200 && botoes < 300) //Senão se o botão de baixo for pressionado
  {
    estadoRELE=0;
    digitalWrite(pinRELE,estadoRELE);
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
else if(botoes > 400 && botoes < 500) //Senão se o botão de cima for pressionado
  {
    estadoRELE=1;
    digitalWrite(pinRELE,estadoRELE);
    trata_botao(); //Tratamento do botão para variar somente 10% quando for clicado
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================TRATAMENTO DOS BOTÕES===========================
void trata_botao()
{
  while(botoes != 1023) //Enquanto o botão não for solto, fica preso no laço
  {
    botoes=analogRead(A0);
  }
}
void trata_botao2()
{
  while(botoes > 900) //Enquanto nenhum botão for pressionado, fica preso no laço
  {
    botoes=analogRead(A0);
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


# include  < LiquidCrystal.h >
# include  < Servo.h >
 
Liquid Crrystal lcd ( 12 , 11 , 5 , 4 , 3 , 2 );
Servo motor;

int tempoDeEspera = 15 ; // segundos
int tempoDociclo = 25 ; // Segundos

void  setup () {
  lcd. começar ( 16 , 2 );
  motor. anexar ( 10 );
  Serial. começar ( 9600 );
  motor. escreva ( 0 );
}

 loop vazio () {
  
  cicloemEspera (tempoDeEspera * 1000 );
  StartCiclo (tempoDoCiclo * 1000 );


  

} // Fim do loop


void  startCiclo ( int tempo) {
      lcd. claro ();
      Alerta ( " Iniciar ciclo " );
      lcd. claro ();
      motor. escreva ( 0 );
      tempo = tempo / 1000 ;
      lcd. setCursor ( 0 , 0 );
      lcd. imprimir ( " Tempo p / Fim " );
      para ( int i = 0 ; i <= (tempo); i ++) {
        lcd. setCursor ( 0 , 1 );
        lcd. imprimir ((tempo) -i);
        atraso ( 1000 );
      }  
}

void  cicloemEspera ( int tempo) {
      lcd. claro ();
      Alerta ( " Terminar ciclo " );
      lcd. claro ();
      motor. escreva ( 35 );
      tempo = tempo / 1000 ;         
      lcd. setCursor ( 0 , 0 );
      lcd. print ( " Tempo p / Inicio " );
      para ( int i = 0 ; i <= (tempo); i ++) {
      lcd. setCursor ( 0 , 1 );
      lcd. imprimir ((tempo) -i);
      atraso ( 1000 );
    }
}



  void  transicao () {  
   para ( int i = 0 ; i <= 16 ; i ++) {
        para ( int j = 0 ; j <= 1 ; j ++) {
        lcd. setCursor (i, j);
        lcd. imprimir ( " * " );
        atraso ( 75 );
        }
 atraso ( 5 );
    }
    lcd. claro ();
   
  } // fim transicao
  
   vazio  Alerta (String msg) {
     
      lcd. claro ();
      lcd. setCursor ( 0 , 0 );
      lcd. imprimir (msg);
      atraso ( 2000 );
   }
  
  
  
  void  msgAlerta (String msg) {
    int tamanho = msg. comprimento ();
    String texto = " " ;
    int spaco = ( 16 -tamanho) / 2 ;
    
    para ( int i = 0 ; i <spaco; i ++) {
      texto + = "  " ;
      String valor = texto + = msg;   
    Serial. println (valor);
    efeitoDuasLinhas (valor);
    atraso ( 200 );
    }
   } // fim msgAlenta
 
  void  effetDuasLinhas (String valor) {
  para ( int i = 0 ; i <= 2 ; i ++) {
        para ( int j = 0 ; j <= 1 ; j ++) {
          lcd. setCursor ( 0 , j);
          lcd. imprimir (valor);
        atraso ( 300 );
        lcd. claro ();
        }
     }
  } // fim efectoDuasLinhas

/ * *
 * Programa para controlar um sistema de irrigação em arduino
 * @author Rafael Lima
 * @version 0.33
 * /

# include  < Time.h >
# include  < TimeAlarms.h >
# include  < LiquidCrystal.h >     // Biblioteca para Display LCD

# incluem  " irduino.h "

# define  PIN_MOLHAR_JARDIM  12
# define  PIN_BACKLIGHT      10

Liquidcrystal lcd ( 8 , 9 , 4 , 5 , 6 , 7 );

byte pinoBotao = A0;

int valorBotao = 0 ;
int opcao_tela = 0 ;

void  setup () {
  Serial. começar ( 9600 );
	setTime ( 6 , 59 , 30 , 2 , 6 , 14 );
  
  pinMode (PIN_MOLHAR_JARDIM, OUTPUT);
  pinMode (PIN_BACKLIGHT, OUTPUT);
  digitalWrite (PIN_BACKLIGHT, LOW);

  desligarIrrigacao ();
  lcd. começar ( 16 , 2 );    // Definindo o LCD com 16 colunas e 2 linhas
  lcd. claro ();
  lcd. setCursor ( 0 , 0 ); // Definindo o cursor na posição inicial do LCD

  Alarme. alarmRepeat ( 7 , 00 , 0 , acionarIrrigacao);  // 7:00 da manhã todos os dias
  Alarme. alarmRepeat ( 7 , 01 , 0 , desligarIrrigacao);  // 7:01 am todos os dias

  Alarme. alarmRepeat ( 12 , 00 , 0 , acionarIrrigacao);  // 12:00 am todos os dias
  Alarme. alarmRepeat ( 12 , 01 , 0 , desligarIrrigacao);  // 12:01 am todos os dias

  Alarme. alarmRepeat ( 18 , 00 , 0 , acionarIrrigacao);  // 6:00 da tarde todos os dias
  Alarme. alarmRepeat ( 18 , 01 , 0 , desligarIrrigacao);  // 6:01 pm todos os dias
}

 loop vazio () {
  valorBotao = analogRead (pinoBotao);
  alternar (opcao_tela) {
      caso UI_MENU:
        menu ();
        quebrar ;
      caso UI_WATER:
        lcdDigitalClockDisplay ();
        lcd. setCursor ( 0 , 1 );
        lcd. imprimir (ALERTA_MOLHANDO);
        quebrar ;
      caso UI_SET_TIME:
        navergarMenuHora ();
        quebrar ;
      caso UI_SET_TIME_HOUR:
        MenuHora_AjusteHora ();
        quebrar ;
      caso UI_SET_TIME_MIN:
        MenuHora_AjusteMin ();
        quebrar ;
      caso UI_SET_TIME_SEC:
        MenuHora_AjusteSec ();
        quebrar ;
      caso UI_TIME:
      padrão :
        lcdDigitalClockDisplay ();
        se ((valorBotao <= BTN_SELECT) && ((valorBotao> BTN_LEFT)))
          opcao_tela = UI_MENU;
        outro
          opcao_tela = UI_TIME;
        quebrar ;
  }
  Alarme. atraso ( 100 );
}

/ *
 * Funções para controle do módulo relé
 * /
anular  acionarIrrigacao () {
  digitalWrite (PIN_MOLHAR_JARDIM, HIGH);
  digitalWrite (PIN_BACKLIGHT, HIGH);
  Serial. println ( " Molhando o Jardim " );
  opcao_tela = UI_WATER;
}

void  desligarIrrigacao () {
  digitalWrite (PIN_MOLHAR_JARDIM, BAIXO);
  digitalWrite (PIN_BACKLIGHT, LOW);
  Serial. println ( " Feixando a torneira " );
  lcd. setCursor ( 0 , 1 );
  lcd. imprimir (LINHA_APAGADA);
  opcao_tela = UI_TIME;
}


/ *
 * Funções para Manipulação do display lcd:
 * Menus E
 * /

vazio  lcdDigitalClockDisplay ()
{
  // exibição do relógio digital do tempo
  lcd. setCursor ( 0 , 0 );
  se ( hora () < 10 )
    lcd. imprimir ( "      " ); // 5c em branco
  outro
    lcd. imprimir ( "     " ); // 4c em branco
  lcd. imprimir ( hora ());
  lcdPrintDigits ( minuto ());
  lcdPrintDigits ( segundo ());
  lcd. imprimir ( "     " ); // 4c em branco
}

vazio  lcdDigitalsetTimeDisplay ()
{
  // exibição do relógio digital do tempo
  lcd. setCursor ( 0 , 0 );
  se ( hora () < 10 )
    lcd. imprimir ( " -     " ); // 5c em branco
  outro
    lcd. imprimir ( " -    " ); // 4c em branco
  lcd. imprimir ( hora ());
  lcdPrintDigits ( minuto ());
  lcdPrintDigits ( segundo ());
  lcd. imprimir ( "    - " ); // 4c em branco
}

vazio  lcdPrintDigits ( int digits)
{
  lcd. imprimir ( " : " );
  se (dígitos < 10 )
     lcd. imprimir ( ' 0 ' );
  lcd. imprimir (dígitos);
}

 menu vazio () {
  lcd. setCursor ( 0 , 1 );
  navegarMenu ();
  lcd. imprimir (MENU_INICIO);
}

void  navegarMenu () {
  valorBotao = analogRead (pinoBotao);
  se (valorBotao <= BTN_RIGHT) {
  } else {
    se (valorBotao <= BTN_UP) {
    } else {
      se (valorBotao <= BTN_DOWN) {
        opcao_tela = UI_SET_TIME;
      } else {
        se (valorBotao <= BTN_LEFT) {
          lcd. setCursor ( 0 , 1 );
          lcd. imprimir (LINHA_APAGADA);
          opcao_tela = UI_TIME;
        } else {
          se (valorBotao <= BTN_SELECT) {
            // faça algo
          }
        }
      }
    }
  }
}

vazio  navergarMenuHora () {
  lcdDigitalClockDisplay ();
        lcd. setCursor ( 0 , 1 );
        lcd. imprimir (MENU_SET_TIME);
        se (valorBotao <= BTN_UP) {
          opcao_tela = UI_MENU;
        } else {
          se (valorBotao <= BTN_SELECT) {
            opcao_tela = UI_SET_TIME_HOUR;
          }
        }
}

anular  MenuHora_AjusteHora () {
  lcdDigitalsetTimeDisplay ();
  lcd. setCursor ( 0 , 1 );
  lcd. imprimir (MENU_SET_TIME_HOUR);
  se (valorBotao <= BTN_RIGHT) {
    opcao_tela = UI_SET_TIME_MIN;
  } else {
    se (valorBotao <= BTN_UP) {
      setTime ( hora () + 1 , minuto (), segundo (), dia (), mês (), ano ());
      Alarme. atraso ( 500 );
    } else {
      se (valorBotao <= BTN_DOWN) {
        setTime ( hora () - 1 , minuto (), segundo (), dia (), mês (), ano ());
        Alarme. atraso ( 500 );
      } else {
        se (valorBotao <= BTN_LEFT) {
            opcao_tela = UI_SET_TIME_SEC;
        } else {
          se (valorBotao <= BTN_SELECT) {
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}

anular  MenuHora_AjusteMin () {
  lcdDigitalsetTimeDisplay ();
  lcd. setCursor ( 0 , 1 );
  lcd. imprimir (MENU_SET_TIME_MIN);
  se (valorBotao <= BTN_RIGHT) {
    opcao_tela = UI_SET_TIME_SEC;
  } else {
    se (valorBotao <= BTN_UP) {
      setTime ( hora (), minuto () + 1 , segundo (), dia (), mês (), ano ());
      Alarme. atraso ( 500 );
    } else {
      se (valorBotao <= BTN_DOWN) {
        setTime ( hora (), minuto () - 1 , segundo (), dia (), mês (), ano ());
        Alarme. atraso ( 500 );
      } else {
        se (valorBotao <= BTN_LEFT) {
            opcao_tela = UI_SET_TIME_HOUR;
        } else {
          se (valorBotao <= BTN_SELECT) {
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}

anular  MenuHora_AjusteSec () {
  lcdDigitalsetTimeDisplay ();
  lcd. setCursor ( 0 , 1 );
  lcd. imprimir (MENU_SET_TIME_SEC);
  se (valorBotao <= BTN_RIGHT) {
    opcao_tela = UI_SET_TIME_HOUR;
  } else {
    se (valorBotao <= BTN_UP) {
      setTime ( hora (), minuto (), segundo () + 1 , dia (), mês (), ano ());
      Alarme. atraso ( 500 );
    } else {
      se (valorBotao <= BTN_DOWN) {
        setTime ( hora (), minuto (), segundo () - 1 , dia (), mês (), ano ());
        Alarme. atraso ( 500 );
      } else {
        se (valorBotao <= BTN_LEFT) {
          opcao_tela = UI_SET_TIME_MIN;
        } else {
          se (valorBotao <= BTN_SELECT) {
            opcao_tela = UI_SET_TIME;
          }
        }
      }
    }
  }
}

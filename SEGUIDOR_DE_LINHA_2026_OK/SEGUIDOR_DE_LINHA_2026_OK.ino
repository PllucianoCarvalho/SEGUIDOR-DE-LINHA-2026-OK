#define ENA 11
#define IN1 8
#define IN2 9

#define ENB 6
#define IN3 10
#define IN4 12

#define VERDE  A0
#define AZUL   A1
#define ROXO   A2
#define CINZA  A3
#define BRANCO A4

#define LINHA HIGH

int velocidadeBase = 255;

// -1 = esquerda
//  1 = direita
int ultimoLado = 1;


// =============================================================
// SETUP
// =============================================================

void setup() {

  Serial.begin(9600);

  pinMode(VERDE, INPUT);
  pinMode(AZUL, INPUT);
  pinMode(ROXO, INPUT);
  pinMode(CINZA, INPUT);
  pinMode(BRANCO, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  parar();
}


// =============================================================
// LOOP
// =============================================================

void loop() {

  bool verde  = digitalRead(VERDE)  == LINHA;
  bool azul   = digitalRead(AZUL)   == LINHA;
  bool roxo   = digitalRead(ROXO)   == LINHA;
  bool cinza  = digitalRead(CINZA)  == LINHA;
  bool branco = digitalRead(BRANCO) == LINHA;


  // ===========================================================
  // CENTRO
  // ===========================================================

  if (roxo) {

    mover(
      velocidadeBase,
      velocidadeBase + 5
    );
  }


  // ===========================================================
  // ESQUERDA SUAVE
  // ===========================================================

  else if (azul) {

    ultimoLado = -1;

    mover(
      110,
      200
    );
  }


  // ===========================================================
  // ESQUERDA FORTE
  // ===========================================================

  else if (verde) {

    ultimoLado = -1;

    mover(
      75,
      210
    );
  }


  // ===========================================================
  // DIREITA SUAVE
  // ===========================================================

  else if (cinza) {

    ultimoLado = 1;

    mover(
      200,
      105
    );
  }


  // ===========================================================
  // DIREITA FORTE
  // ===========================================================

  else if (branco) {

    ultimoLado = 1;

    mover(
      210,
      75
    );
  }


  // ===========================================================
  // NENHUM SENSOR
  // ===========================================================

  else {

    if (ultimoLado == -1) {

      mover(
        0,
        100
      );
    }

    else {

      mover(
        100,
        0
      );
    }
  }


  // ===========================================================
  // MONITOR SERIAL
  // ===========================================================

  Serial.print(verde);
  Serial.print(" ");
  Serial.print(azul);
  Serial.print(" ");
  Serial.print(roxo);
  Serial.print(" ");
  Serial.print(cinza);
  Serial.print(" ");
  Serial.println(branco);

  delay(5);
}


// =============================================================
// MOVER MOTORES
// =============================================================

void mover(
  int velocidadeEsquerda,
  int velocidadeDireita
) {

  // MOTOR DIREITO

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);


  // MOTOR ESQUERDO

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  // MOTOR ESQUERDO

  analogWrite(
    ENB,
    constrain(
      velocidadeEsquerda,
      0,
      255
    )
  );


  // MOTOR DIREITO

  analogWrite(
    ENA,
    constrain(
      velocidadeDireita,
      0,
      255
    )
  );
}


// =============================================================
// PARAR
// =============================================================

void parar() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
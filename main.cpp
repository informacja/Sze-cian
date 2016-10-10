
#include <GL/gl.h>
#include <stdlib.h>

// sta�e do obs�ugi menu podr�cznego

enum
{
    FULL_WINDOW, // aspekt obrazu - ca�e okno
    ASPECT_1_1, // aspekt obrazu 1:1
    EXIT // wyj�cie
};

// aspekt obrazu

int Aspect = FULL_WINDOW;

// wp�rz�dne po�o�enia obserwatora

GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 3;

// wsp�rz�dne punktu w kt�rego kierunku jest zwr�cony obserwator,

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = - 100;

// funkcja generuj�ca scen� 3D

void Display()
{
    // kolor t�a - zawarto�� bufora koloru
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    
    // wyb�r macierzy modelowania
    glMatrixMode( GL_MODELVIEW );
    
    // macierz modelowania = macierz jednostkowa
    glLoadIdentity();
    
    // ustawienie obserwatora
    gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0 );
    
    // kolor kraw�dzi sze�cianu
    glColor3f( 0.0, 0.0, 0.0 );
    
    // pocz�tek definicji kraw�dzi sze�cianu
    glBegin( GL_LINES );
    
    // wsp�lrz�dne kolejnych kraw�dzi sze�cianu
    glVertex3f( 1.0, 1.0, 1.0 );
    glVertex3f( 1.0, - 1.0, 1.0 );
    
    glVertex3f( 1.0, - 1.0, 1.0 );
    glVertex3f( 1.0, - 1.0, - 1.0 );
    
    glVertex3f( 1.0, - 1.0, - 1.0 );
    glVertex3f( 1.0, 1.0, - 1.0 );
    
    glVertex3f( 1.0, 1.0, - 1.0 );
    glVertex3f( 1.0, 1.0, 1.0 );
    
    glVertex3f( - 1.0, 1.0, 1.0 );
    glVertex3f( - 1.0, - 1.0, 1.0 );
    
    glVertex3f( - 1.0, - 1.0, 1.0 );
    glVertex3f( - 1.0, - 1.0, - 1.0 );
    
    glVertex3f( - 1.0, - 1.0, - 1.0 );
    glVertex3f( - 1.0, 1.0, - 1.0 );
    
    glVertex3f( - 1.0, 1.0, - 1.0 );
    glVertex3f( - 1.0, 1.0, 1.0 );
    
    glVertex3f( 1.0, 1.0, 1.0 );
    glVertex3f( - 1.0, 1.0, 1.0 );
    
    glVertex3f( 1.0, - 1.0, 1.0 );
    glVertex3f( - 1.0, - 1.0, 1.0 );
    
    glVertex3f( 1.0, - 1.0, - 1.0 );
    glVertex3f( - 1.0, - 1.0, - 1.0 );
    
    glVertex3f( 1.0, 1.0, - 1.0 );
    glVertex3f( - 1.0, 1.0, - 1.0 );
    
    // koniec definicji prymitywu
    glEnd();
    
    // skierowanie polece� do wykonania
    glFlush();
    
    // zamiana bufor�w koloru
    glutSwapBuffers();
}

// zmiana wielko�ci okna

void Reshape( int width, int height )
{
    // obszar renderingu - ca�e okno
    glViewport( 0, 0, width, height );
    
    // wyb�r macierzy rzutowania
    glMatrixMode( GL_PROJECTION );
    
    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();
    
    // parametry bry�y obcinania
    if( Aspect == ASPECT_1_1 )
    {
        // wysoko�� okna wi�ksza od wysoko�ci okna
        if( width < height && width > 0 )
             glFrustum( - 2.0, 2.0, - 2.0 * height / width, 2.0 * height / width, 1.0, 5.0 );
        else
        
        // szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
        if( width >= height && height > 0 )
             glFrustum( - 2.0 * width / height, 2.0 * width / height, - 2.0, 2.0, 1.0, 5.0 );
        
    }
    else
         glFrustum( - 2.0, 2.0, - 2.0, 2.0, 1.0, 5.0 );
    
    // generowanie sceny 3D
    Display();
}

// obs�uga klawiatury

void Keyboard( unsigned char key, int x, int y )
{
    // klawisz +
    if( key == '+' )
         eyez -= 0.1;
    else
    
    // klawisz -
    if( key == '-' )
         eyez += 0.1;
    
    // odrysowanie okna
    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

// obs�uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys( int key, int x, int y )
{
    switch( key )
    {
        // kursor w lewo
    case GLUT_KEY_LEFT:
        eyex += 0.1;
        break;
        
        // kursor w g�r�
    case GLUT_KEY_UP:
        eyey -= 0.1;
        break;
        
        // kursor w prawo
    case GLUT_KEY_RIGHT:
        eyex -= 0.1;
        break;
        
        // kursor w d�
    case GLUT_KEY_DOWN:
        eyey += 0.1;
        break;
    }
    
    // odrysowanie okna
    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

// obs�uga menu podr�cznego

void Menu( int value )
{
    switch( value )
    {
        // obszar renderingu - ca�e okno
    case FULL_WINDOW:
        Aspect = FULL_WINDOW;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;
        
        // obszar renderingu - aspekt 1:1
    case ASPECT_1_1:
        Aspect = ASPECT_1_1;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;
        
        // wyj�cie
    case EXIT:
        exit( 0 );
    }
}

int main( int argc, char * argv[] )
{
    // inicjalizacja biblioteki GLUT
    glutInit( & argc, argv );
    
    // inicjalizacja bufora ramki
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    
    // rozmiary g��wnego okna programu
    glutInitWindowSize( 400, 400 );
    
    // utworzenie g��wnego okna programu
    #ifdef WIN32
    
    glutCreateWindow( "Sze�cian 4" );
    #else
    
    glutCreateWindow( "Szescian 4" );
    #endif
    
    // do��czenie funkcji generuj�cej scen� 3D
    glutDisplayFunc( Display );
    
    // do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
    glutReshapeFunc( Reshape );
    
    // do��czenie funkcji obs�ugi klawiatury
    glutKeyboardFunc( Keyboard );
    
    // do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
    glutSpecialFunc( SpecialKeys );
    
    // utworzenie menu podr�cznego
    glutCreateMenu( Menu );
    
    // dodanie pozycji do menu podr�cznego
    #ifdef WIN32
    
    glutAddMenuEntry( "Aspekt obrazu - ca�e okno", FULL_WINDOW );
    glutAddMenuEntry( "Aspekt obrazu 1:1", ASPECT_1_1 );
    glutAddMenuEntry( "Wyj�cie", EXIT );
    #else
    
    glutAddMenuEntry( "Aspekt obrazu - cale okno", FULL_WINDOW );
    glutAddMenuEntry( "Aspekt obrazu 1:1", ASPECT_1_1 );
    glutAddMenuEntry( "Wyjscie", EXIT );
    #endif
    
    // okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
    glutAttachMenu( GLUT_RIGHT_BUTTON );
    
    // wprowadzenie programu do obs�ugi p�tli komunikat�w
    glutMainLoop();
    return 0;
}

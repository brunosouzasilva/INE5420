/* Teste de unidade de window.h */

#include "render/window.h"

#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerDouble.h"

#include "render/clipping/clippingArea.h"
#include "math/constant.h"

DECLARE_TEST( WindowTest ) {
    bool b = true;

    ClippingArea c{0, 0, 1, 1};
    Window w( c );
    w.move({0.5, 0});

    b &= Test::TEST_EQUALS( w.x, 1.0 );
    b &= Test::TEST_EQUALS( w.y, 0.5 );
    b &= Test::TEST_EQUALS( w.w, 1.0 );
    b &= Test::TEST_EQUALS( w.h, 1.0 );
    b &= Test::TEST_EQUALS( w.t, 0.0 );
    /* Aqui podemos usar igualdade pois estes números são
     * representáveis por completo em double. */

    Test::TesterDouble d(2); //2 * Epsilon de máquina

    w.rotate( Math::PI/6 );
    w.moveUp( {0, 1.0} );
    w.rotate( -Math::PI/6 );
    w.moveUp( {1.0, 0} );
    w.rotate( Math::PI/3 );
    w.moveUp( {-1.0, 0} );
    w.rotate( -Math::PI/3 );
    //Agora, devemos ter voltado para o ponto inicial.

    b &= d.TEST_EQUALS( w.x, 1.0 );
    b &= d.TEST_EQUALS( w.y, 0.5 ); //Este não passa com epsilon de máquina.
    b &= d.TEST_EQUALS( w.w, 1.0 );
    b &= d.TEST_EQUALS( w.h, 1.0 );
    b &= d.TEST_EQUALS( w.t, 0.0 );

    //Testes de escala:
    w.vscale( 2.0 );
    w.hscale( 3.0 );
    b &= Test::TEST_EQUALS( w.h, 2.0 );
    b &= Test::TEST_EQUALS( w.w, 3.0 );
    b &= Test::TEST_EQUALS( w.area(), 6.0 );

    return b;
}

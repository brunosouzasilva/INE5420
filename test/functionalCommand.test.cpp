/* functionalCommand.test.cpp
 * Teste de unidade para a classe FunctionalCommand
 */

#include "command/functionalCommand.h"

#include <string>
#include "command/commandFactory.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

namespace {
    /* Todas as funções atualizarão este valor booleano para verdadeiro
     * sempre que forem chamadas corretamente */
    bool b = true;

    void f() {
        b = true;
    }
    
    void g( int i ) {
        b = Test::TEST_EQUALS( i, 42 );
    }
} // anonymous namespace

DECLARE_TEST( FunctionalCommandTest ) {
    using std::string;
    using std::istringstream;

    bool b = true;

    istringstream is1( "" );
    Command * c = CommandFactory::makeFunctional( f );

    ::b = false;
    c->interpret( is1 );
    b &= ::b;

    delete c;

    istringstream is2( "       +42   " );
    Command * d = CommandFactory::makeFunctional( g );
    ::b = false;
    d->interpret( is2 );
    b &= ::b;

    bool alce = false;

    istringstream is3( "23" );
    Command * e = CommandFactory::makeFunctional<int>(
        [&alce]( int i ){
            alce = Test::TEST_EQUALS( i, 23 );
        } );
    e->interpret( is3 );
    b &= alce;

    alce = false;
    Command * f = CommandFactory::makeFunctional(
        [&alce](){
            alce = true;
        } );
    f->interpret( is3 );
    b &= alce;

    return b;
}

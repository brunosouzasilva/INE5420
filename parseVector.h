/* parseVector.h
 * Especialização de ParseType que lê um Math::Vector.
 * A sintaxe é a mesma de um vector<double>; valores adicionais
 * serão ignorados, valores faltantes serão substituídos por 0.0,
 * exceto o último, que será substituído por 1.0.
 *
 * Note que, como Math::Vector é um typedef, assim como Math::Point,
 * esta classe automaticamente define especializações que leem pantos. */
#ifndef PARSE_VECTOR_H
#define PARSE_VECTOR_H

#include <vector>
#include "command/parseType.h"
#include "math/vector.h"

template< int N >
struct ParseType< Math::Vector<N> > {
    static Math::Vector<N> parse( std::istringstream& is ) {
        std::vector<double> vec = ParseType<std::vector<double>>::parse( is );
        Math::Vector<N> r; //Inicializa tudo em zero
        int i = 0;
        auto it = vec.begin();
        for( ; i < N && it != vec.end(); ++i, ++it )
            r[i] = *it;
        if( i < N ) // i<N implica que o que parou o 'for' não foi i<N.
            r[N-1] = 1.0;

        return r;
    }
};

#endif // PARSE_VECTOR_H

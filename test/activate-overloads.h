// activate-overloads.h
#include <order/interpreter.h>

#define ORDER_PP_DEF_8dispatch_overload ORDER_PP_FN( \
8fn(8N, 8V, \
    8do( \
        8print( 8cat(8(static inline int DISPATCH_OVER_), 8N) ((int ac, int av[]) { return ) ), \
        8seq_for_each_with_idx( \
            8fn(8I, 8T, \
                8let( (8S, 8tuple_to_seq(8tuple_at_1(8T))), \
                    8print( 8lparen (ac==) 8to_lit(8seq_size(8S)) ), \
                    8seq_for_each_with_idx(8fn(8I, 8T, 8print( (&&av[) 8I (]==) 8cat(8(K_), 8T) )), 0, 8S), \
                    8print( 8rparen (?) 8I (:) ) \
                )), \
            1, 8V), \
        8print( ( -1; }) ) \
    ) ))

#define TYPES_TO_ENUMS(TS) ORDER_PP ( \
    8do( \
        8seq_for_each(8fn(8T, 8print( 8T (:) 8cat(8(K_), 8T) (,) )), \
                      8tuple_to_seq(8(TS))), \
        8print( (default: -1) ) \
    ) \
)
#define ENUMERATE_TYPES(TS) enum OVERLOAD_TYPEK { ORDER_PP ( \
    8seq_for_each(8fn(8V, 8print( 8V (,) )), 8types_to_vals(8tuple_to_seq(8(TS)))) \
) };
#define ORDER_PP_DEF_8types_to_vals ORDER_PP_FN( \
8fn(8S, 8seq_map(8fn(8T, 8cat(8(K_), 8T)), 8S)) )


ENUMERATE_TYPES(OVERLOAD_ARG_TYPES)
#define OVER_ARG_TYPE(V) _Generic((V), TYPES_TO_ENUMS(OVERLOAD_ARG_TYPES) )

#define OVERLOAD
ORDER_PP (
    8seq_for_each(
        8fn(8F,
            8lets( (8D, 8expand(8adjoin( 8F, 8(()) )))
                   (8O, 8seq_drop(2, 8tuple_to_seq(8D))),
                8dispatch_overload(8F, 8O) )),
        8tuple_to_seq(8(OVERLOAD_FUNCTIONS))
    )
)
#undef OVERLOAD

#define OVERLOAD(N, ARGS, ...) ORDER_PP ( \
    8do( \
        8print(8lparen), \
        8seq_for_each_with_idx( \
            8fn(8I, 8T, \
                8lets( (8S, 8tuple_to_seq(8tuple_at_1(8T))) \
                       (8R, 8tuple_to_seq(8(ARGS))) \
                       (8N, 8tuple_at_0(8T)), \
                    8if(8equal(8seq_size(8S), 8seq_size(8R)), \
                        8do( \
                            8print( 8lparen (DISPATCH_OVER_##N) 8lparen 8to_lit(8seq_size(8R)) (,(int[]){) ), \
                            8seq_for_each(8fn(8A, 8print( (OVER_ARG_TYPE) 8lparen 8A 8rparen (,) )), 8R), \
                            8print( (-1}) 8rparen (==) 8I 8rparen (?) 8N 8lparen ), \
                            8let( (8P, 8fn(8A, 8T, \
                                           8print( (_Generic) 8lparen 8lparen 8A 8rparen (,) 8T (:) 8A (,default:*) 8lparen 8T (*) 8rparen (0) 8rparen ) \
                                           )), \
                                8ap(8P, 8seq_head(8R), 8seq_head(8S)), \
                                8seq_pair_with(8fn(8A, 8T, 8do(8print((,)), 8ap(8P, 8A, 8T))), 8seq_tail(8R), 8seq_tail(8S)) \
                            ), \
                            8print( 8rparen (:) ) \
                        ), \
                        8print(( )) ) \
                )), \
            1, 8tuple_to_seq(8((__VA_ARGS__))) \
        ), \
        8print( 8cat(8(N), 8(_default)) (()) 8rparen) \
    ) \
)

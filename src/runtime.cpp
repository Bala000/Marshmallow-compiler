//
// Created by Ejaz on 4/12/2018.
//
// Runtime for Marshmellow
//


#include <iostream>
#include <vector>
#include "bytecode.h"
#include "runtime.h"

#define STACK_SIZE 200
#define TRUE 1
#define FALSE 0

int nglobals = -1;
std::vector<int> globals;

void add_global(int ind, int val){

    if(ind > nglobals){
        nglobals++;
        globals.push_back(val);
    }else{
        globals.at(ind) = val;
    };
}

int get_global(int ind){

    return globals.at(ind);
}

void run(int *code, int codelen) {
    int ip = code[0];
    run(code, codelen, ip);
}

void run(int *code, int codelen, int ip) {
    int sp = -1;
    int a = 0;
    int b = 0;

    int stack[STACK_SIZE];
    int opcode = code[ip];
    context *ctx = new context(NULL, 0);
    while (ip < codelen) {
        ip++;
        switch (opcode) {
            case PUSH: {
                stack[++sp] = code[ip++];
                break;
            }
            case POP: {
                sp--;
                break;
            }
            case STORE: {
                ctx->add_local(code[ip++], stack[sp--]);
                break;
            }
            case LOAD: {
                stack[++sp] = ctx->get_local(code[ip++]);
                break;
            }
            case GSTORE: {
                add_global(code[ip++], stack[sp--]);
                break;
            }
            case GLOAD: {
                stack[++sp] = get_global(code[ip++]);
                break;
            }
            case ADD: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a + b;
                break;
            }
            case SUB: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a - b;
                break;
            }
            case MUL: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a * b;
                break;
            }
            case DIV: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a / b;
                break;
            }
            case MOD: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a % b;
                break;
            }
            case EQ: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a == b ? TRUE : FALSE;
                break;
            }
            case NEQ: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a != b ? TRUE : FALSE;
                break;
            }
            case LT: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a < b ? TRUE : FALSE;
                break;
            }
            case GT: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a > b ? TRUE : FALSE;
                break;
            }
            case LTE: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a <= b ? TRUE : FALSE;
                break;
            }
            case GTE: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a >= b ? TRUE : FALSE;
                break;
            }
            case NOT: {
                a = stack[sp--];
                stack[++sp] = !a;
                break;
            }
            case AND: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a & b;
                break;
            }
            case OR: {
                a = stack[sp--];
                b = stack[sp--];
                stack[++sp] = a | b;
                break;
            }
            case PRINT: {
                a = stack[sp--];
                std::cout << a << std::endl;
                break;
            }
            case BRF: {
                a = stack[sp--];
                if (a == FALSE)
                    ip = code[ip];
                else
                    ip++;
                break;
            }
            case BR: {
                ip = code[ip];
                break;
            }
            case NOOP: {
                ip++;
                break;
            }
            case CALL: {
                int new_ip = code[ip++];
                a = code[ip++]; //Param count
                context *new_ctx = new context(ctx, ip);
                ctx = new_ctx;
                for (int i = 0; i < a; i++) {
                    ctx->add_local(i, stack[sp--]);
                }
                ip = new_ip;
                break;
            }
            case RET: {
                context *old_ctx = ctx;
                ip = ctx->return_ip;
                ctx = ctx->caller_context;
                delete (old_ctx);
                break;
            }
            case EXIT: {
                delete (ctx);
                globals.clear();
                std::cout << "Program exited successfully" << std::endl;
                break;
            }
            default: {
                delete (ctx);
                globals.clear();
                std::cout << "Program exited. Something went wrong." << std::endl;
                break;
            }
        }
        opcode = code[ip];
    }
}

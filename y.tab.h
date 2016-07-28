
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LITERAL = 258,
     DOUBLE_LITERAL = 259,
     IDENTIFIER = 260,
     FUNCTION = 261,
     IF = 262,
     ELSE = 263,
     ELSEIF = 264,
     WHILE = 265,
     FOR = 266,
     RETURN_T = 267,
     BREAK = 268,
     CONTINUE = 269,
     NULL_T = 270,
     LP = 271,
     RP = 272,
     LC = 273,
     RC = 274,
     SEMICOLON = 275,
     COMMA = 276,
     ASSIGN = 277,
     LOGICAL_AND = 278,
     LOGICAL_OR = 279,
     EQ = 280,
     NE = 281,
     GT = 282,
     GE = 283,
     LT = 284,
     LE = 285,
     ADD = 286,
     SUB = 287,
     MUL = 288,
     DIV = 289,
     MOD = 290,
     TRUE_T = 291,
     FALSE_T = 292,
     GLOBAL_T = 293
   };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define DOUBLE_LITERAL 259
#define IDENTIFIER 260
#define FUNCTION 261
#define IF 262
#define ELSE 263
#define ELSEIF 264
#define WHILE 265
#define FOR 266
#define RETURN_T 267
#define BREAK 268
#define CONTINUE 269
#define NULL_T 270
#define LP 271
#define RP 272
#define LC 273
#define RC 274
#define SEMICOLON 275
#define COMMA 276
#define ASSIGN 277
#define LOGICAL_AND 278
#define LOGICAL_OR 279
#define EQ 280
#define NE 281
#define GT 282
#define GE 283
#define LT 284
#define LE 285
#define ADD 286
#define SUB 287
#define MUL 288
#define DIV 289
#define MOD 290
#define TRUE_T 291
#define FALSE_T 292
#define GLOBAL_T 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 7 "yap.y"

    char           *identifier;
	double         double_value;
    Statement      *statement;



/* Line 1676 of yacc.c  */
#line 136 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



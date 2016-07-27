
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
     FUNCTION = 258,
     IF = 259,
     ELSE = 260,
     ELSEIF = 261,
     WHILE = 262,
     FOR = 263,
     RETURN_T = 264,
     BREAK = 265,
     CONTINUE = 266,
     NULL_T = 267,
     LP = 268,
     RP = 269,
     LC = 270,
     RC = 271,
     SEMICOLON = 272,
     COMMA = 273,
     ASSIGN = 274,
     LOGICAL_AND = 275,
     LOGICAL_OR = 276,
     EQ = 277,
     NE = 278,
     GT = 279,
     GE = 280,
     LT = 281,
     LE = 282,
     ADD = 283,
     SUB = 284,
     MUL = 285,
     DIV = 286,
     MOD = 287,
     TRUE_T = 288,
     FALSE_T = 289,
     GLOBAL_T = 290
   };
#endif
/* Tokens.  */
#define FUNCTION 258
#define IF 259
#define ELSE 260
#define ELSEIF 261
#define WHILE 262
#define FOR 263
#define RETURN_T 264
#define BREAK 265
#define CONTINUE 266
#define NULL_T 267
#define LP 268
#define RP 269
#define LC 270
#define RC 271
#define SEMICOLON 272
#define COMMA 273
#define ASSIGN 274
#define LOGICAL_AND 275
#define LOGICAL_OR 276
#define EQ 277
#define NE 278
#define GT 279
#define GE 280
#define LT 281
#define LE 282
#define ADD 283
#define SUB 284
#define MUL 285
#define DIV 286
#define MOD 287
#define TRUE_T 288
#define FALSE_T 289
#define GLOBAL_T 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 6 "yap.y"

	 



/* Line 1676 of yacc.c  */
#line 128 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



//-*-C++-*-

#ifndef JSONPARSER_JSON_ENUMERATIONS_H
#define JSONPARSER_JSON_ENUMERATIONS_H

namespace JsonParser 
{
  /*
    Characters are mapped into these 31 character classes. This allows for
    a significant reduction in the size of the state transition table.
    */
  enum JSON_character_class 
    {
      C_SPACE,  /* space */
      C_WHITE,  /* other whitespace */
      C_LPARN,  /* (  */
      C_RPARN,  /* ) */
      C_LCURB,  /* {  */
      C_RCURB,  /* } */
      C_LSQRB,  /* [ */
      C_RSQRB,  /* ] */
      C_COLON,  /* : */
      C_COMMA,  /* , */
      C_QUOTE,  /* " */
      C_BACKS,  /* \ */
      C_SLASH,  /* / */
      C_PLUS,   /* + */
      C_MINUS,  /* - */
      C_POINT,  /* . */
      C_ZERO ,  /* 0 */
      C_DIGIT,  /* 123456789 */
      C_LOW_A,  /* a */
      C_LOW_B,  /* b */
      C_LOW_C,  /* c */
      C_LOW_D,  /* d */
      C_LOW_E,  /* e */
      C_LOW_F,  /* f */
      C_LOW_L,  /* l */
      C_LOW_N,  /* n */
      C_LOW_R,  /* r */
      C_LOW_S,  /* s */
      C_LOW_T,  /* t */
      C_LOW_U,  /* u */
      C_LOW_Y,  /* y */
      C_ABCDF,  /* ABCDF */
      C_E,      /* E */
      C_ETC,    /* everything else */
      C_STAR,   /* * */   
      C_EOF,    /* end of file */
      C_ERR,    /* error */
      NR_CLASSES
    }

  typedef JSON_character_class CharacterClass;//JSON_character_class_type;

}

#endif

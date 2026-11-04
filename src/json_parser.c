#include "json_parser.h"
#include "json_lexer.h"
#include <stdio.h>
#include <string.h>

// Print out the tokens to make sure we parsed them correctly
void print_token(char *json_text, Token_t *token) {
  switch (token->token_type) {
  case LBRACE_TOK:
    printf("\nOpening object\n");
    break;
  case RBRACE_TOK:
    printf("\nClose object\n");
    break;
  case LBRACKET_TOK:
    printf("Open array\n");
    break;
  case RBRACKET_TOK:
    printf("Close array\n");
    break;
  case COLON_TOK:
    printf(": ");
    break;
  case COMMA_TOK:
    printf(",\n");
    break;
  case STR_TOK: {
    // print string content within quotes
    size_t length = token->value.str_slice.length + 1;
    // Pointer arithmatic to find the address of the start of our string val
    char *start_offset = token->value.str_slice.start;
    char str[length];

    // Null terminate the string
    str[length] = '\0';

    // slice and print
    snprintf(str, length, "%s", start_offset);
    printf("\"%s\"", str);
    break;
  }
  case NUM_TOK:
    // print out the number
    printf("%f", token->value.number_value);
    break;
  default:
    printf("Misc Token\n");
  }
}

int parse_json(char *json_text, JsonNode_t *out_ptr) {
  // Initialize our lexer
  Lexer_t lexer;
  init_lexer(&lexer, json_text, strlen(json_text));

  // Convert text into "tokens"
  int token_result = tokenize_json(&lexer);
  if (token_result < 0) {
    return token_result;
  }

  // Print output to make sure nothing is bugged (it is)
  for (size_t i = 0; i < lexer.token_list->count; i++) {
    Token_t *token = array_get(lexer.token_list, i);
    print_token(json_text, token);
  }
  return 0;
}

int build_tree(const ArrayList *tokens, JsonNode_t *json_tree) { return 0; }

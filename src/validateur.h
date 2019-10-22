#ifndef __VALIDATEUR_H__
#define __VALIDATEUR_H__

int validateur_content_message_json(
  char *message
);

int validateur_format_message_json(
  char *message
);

int validateur_guille_format_message_json(
  char *message
);

int validateur_accolades_format_message_json(
  char *message
);

int validateur_code_format_message_json(
  char 	*message,
  int	i
);

int validateur_char_format_message_json(
  char 	*message,
  int	i,
  char 	char_test
);

int validateur_valeurs_format_message_json(
  char 	*message,
  int	i
);

int validateur_guille_after_format_message_json(
  char 	*message,
  int	i
);


#endif

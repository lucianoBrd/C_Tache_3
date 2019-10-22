#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validateur.h"

int validateur_content_message_json(
  char *message
){
  message_json *json;
  
  json = create_object_json(message);
  
  if(	strcmp(json->code, "message")  	!= 0 &&
    	strcmp(json->code, "nom") 	!= 0 &&
    	strcmp(json->code, "calcule")  	!= 0 &&
    	strcmp(json->code, "couleurs") 	!= 0 ){
    delete_message_json(json);
    return -1;

  } /* Check if code is correct */
  
  if( strcmp(json->code, "message") == 0 ||
      strcmp(json->code, "nom")     == 0 ){
    if(json->nb_valeurs != 1){
      delete_message_json(json);
      return -1;
      
    }
  }
  
  if(strcmp(json->code, "calcule") == 0){
    if(json->nb_valeurs != 3){
      delete_message_json(json);
      return -1;
      
    }
  }
  
  if(strcmp(json->code, "couleurs") == 0){
    if(json->nb_valeurs > 1){
      delete_message_json(json);
      return -1;
      
    }
  }
  
  delete_message_json(json);
}

int validateur_format_message_json(
  char *message
){
  int 	i = 0;
  
  if(validateur_guille_format_message_json(message) < 0){
    return -1;
    
  }
  
  if(validateur_accolades_format_message_json(message) < 0){
    return -1;
    
  } /* Test there are the accolades */  
  
  /* Test there is the "code" */
  i = validateur_code_format_message_json(message, i);
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is : after "code" */
  i = validateur_char_format_message_json(message, i, ':');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is " after "code" : */
  i = validateur_char_format_message_json(message, i, '"');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is " after "code" : "string */
  i = validateur_char_after_format_message_json(message, i, '"');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is , after "code" : "string" */
  i = validateur_char_format_message_json(message, i, ',');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is the valeurs */
  i = validateur_valeurs_format_message_json(message, i);
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is : after "valeurs" */
  i = validateur_char_format_message_json(message, i, ':');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is [ after "valeurs" : */
  i = validateur_char_format_message_json(message, i, '[');
  
  if(i < 0){
    return -1;
    
  }
  
  /* Test there is ] after "valeurs" : [... */
  if(validateur_char_after_format_message_json(message, i, ']') < 0){
    return -1;
    
  }
  
    
  return 0;
  
}

int validateur_guille_format_message_json(
  char *message
){
  int i = 0,
      count = 0;
  /* Count number of " */
  while(message[i] != '\0'){
    if(message[i] == '"'){
      count++;
    
    }
    i++;
  }
  
  if(count%2 != 0){
    return -1;
    
  }
  return i;
  
}

int validateur_accolades_format_message_json(
  char *message
){
  char 	accolade_first = ' ', 
	accolade_last;
  int 	accolade_first_c = 0,
	i = 0;
  /* Test there are the accolades */
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if(accolade_first_c == 0){
	accolade_first = message[i];
	accolade_first_c = 1;
      }
      accolade_last = message[i];
    
    }
    i++;
  }
  
  if(accolade_first != '{' || accolade_last != '}'){
    return -1;
    
  }
  return i;
  
}

int validateur_code_format_message_json(
  char 	*message,
  int	i
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != '{' && message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if( i > 4				&&
	  message[i]     == 'e' 	&&
	  message[i - 1] == 'd' 	&&
	  message[i - 2] == 'o' 	&&
	  message[i - 3] == 'c' 	&&
	  message[i + 1] == '"' 	&&
	  message[i - 4] == '"' 	){
	valid = 0;
	break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i = i + 2;
  return i;
  
}

int validateur_char_format_message_json(
  char 	*message,
  int	i,
  char 	char_test
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if(message[i] == char_test){
	valid = 0;
	break;
	
      } else {
	break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i++;
  return i;
  
}

int validateur_valeurs_format_message_json(
  char 	*message,
  int	i
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] != ' ' && message[i] != '\n' && message[i] != '\r'){
      if( i > 7 			&&
	  message[i]     == 's' 	&&
	  message[i - 1] == 'r' 	&&
	  message[i - 2] == 'u' 	&&
	  message[i - 3] == 'e' 	&&
	  message[i - 4] == 'l' 	&&
	  message[i - 5] == 'a' 	&&
	  message[i - 6] == 'v' 	&&
	  message[i + 1] == '"' 	&&
	  message[i - 7] == '"' 	){
	valid = 0;
	break;
	
      }
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i = i + 2;
  return i;
  
}

int validateur_char_after_format_message_json(
  char 	*message,
  int	i,
  char	char_test
){
  int valid = -1;
  while(message[i] != '\0'){
    if(message[i] == char_test){
      valid = 0;
      break;
      
    }
    i++;
  }
  
  if(valid != 0){
    return -1;
    
  }
  i++;
  return i;
  
}
#ifndef DICT_H
#define DICT_H
/*
 * Function: get_word
 * Description: Returns random line with word from dictionary file.
 * Return Value:
 *   Pointer to a string representing a random line from file, or NULL at error.
 */
char *get_word(const char *dict);
/*
 * Function: is_word_in_dict
 * Description: Checks if a word is in dictionary file
 * Arguments:
 *   word - The word that will be searched
 *   dict - Path to dictionary file
 * Return Value:
 *   1 if word is in dictionary, 0 if it's not, -1 on error.
 */
int is_word_in_dict(const char *word, const char *dict);
/*
 * Function: char_exists
 * Description: Checks if char already exists in array
 * Arguments:
 *   ch - Char that will be searched
 *   array - Array where will char be searched
 * Return Value:
 *   true if char exists in array, false if wasn't found.
 */
bool char_exists(char ch, char arr[]);
/*
 * Function: copy_char_to_array
 * Description: Copies char to the end of the array, if it's not already present in array.
 * Arguments:
 *   ch - Char that will be copied
 *   array - Array that will be char copied to
 * Return Value:
 *   true if successfully copied to the end of array, false if char was already present.
 */
bool copy_char_to_array(char ch, char *array);
#endif

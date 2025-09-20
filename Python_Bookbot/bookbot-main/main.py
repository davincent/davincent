def main():
    book_path = "books/frankenstein.txt"
    text = get_book_text(book_path)
    num_words = get_num_words(text)
    num_letters = get_num_letters(text)
    sorted_transformed_list = divide_dict(num_letters)
    print(f"--- Begin report of books/frankenstein.txt --- \n {num_words} words found in the document \n")
    for item in sorted_transformed_list:
        print(f"The '{item["letter"]}' character was founr {item["count"]} times")
    print("--- End of report ---")


# Get the number of words in the text
def get_num_words(text):
    words = text.split()
    return len(words)

# Create the path to the text file
def get_book_text(path):
    with open(path) as f:
        return f.read()
        
# Get the count of each letter
def get_num_letters(text):
    lowercase_text = text.lower()
    num_letter_dict = {}
    letters = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
    for letter in letters:
        num_letter_dict[letter] = lowercase_text.count(letter)
    return num_letter_dict

def sort_on_count(dict_item):
    return dict_item["count"]

def divide_dict(num_letters):
    transformed_list = [{"letter": key, "count": value} for key, value in num_letters.items()]
    # Sort the list of dictionaries by the "count" key in descending order using the sort_on_count function
    transformed_list.sort(reverse=True, key=sort_on_count)
    return transformed_list



main()
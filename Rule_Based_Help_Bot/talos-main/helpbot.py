rules = {
    # Intent 1: Password & Account Issues
    "password": "Please use the 'Reset my Password' below the password field to reset your own password.",
    "login": "Please use the 'Reset my Password' below the password field to reset your own password.",
    "locked": "Please use the 'Reset my Password' below the password field to reset your own password.",
    "account": "Please use the 'Reset my Password' below the password field to reset your own password.",
    "reset": "Please use the 'Reset my Password' below the password field to reset your own password.",

    # Intent 2: Network Connectivity Problems
    "internet": "Okay, let's troubleshoot your network. Can you tell me if this is affecting a specific website or all of your internet access?",
    "network": "Okay, let's troubleshoot your network. Can you tell me if this is affecting a specific website or all of your internet access?",
    "wifi": "Okay, let's troubleshoot your network. Can you tell me if this is affecting a specific website or all of your internet access?",
    "connect": "Okay, let's troubleshoot your network. Can you tell me if this is affecting a specific website or all of your internet access?",

    # Intent 3: Printer & Hardware Issues
    "printer": "I can help with common printer problems. Are you getting an error message? Or is the printer not responding?",
    "print": "I can help with common printer problems. Are you getting an error message? Or is the printer not responding?",
    "scanner": "I can help with common printer problems. Are you getting an error message? Or is the printer not responding?",
    "computer": "Please restart your device. If the problem persists, please provide the model number of the hardware you are having issues with.",
    "screen": "Please restart your device. If the problem persists, please provide the model number of the hardware you are having issues with.",

    # Intent 4: Software/Application Problems
    "software": "What software are you having trouble with? Can you please describe the issue in a few more words?",
    "app": "What software are you having trouble with? Can you please describe the issue in a few more words?",
    "program": "What software are you having trouble with? Can you please describe the issue in a few more words?",

    # Intent 5: General Help and Greeting
    "help": "Hello! I'm a rule-based IT assistant. I can help with common issues like password resets, network problems, and software troubleshooting. What seems to be the problem today?",
    "hello": "Hello! I'm a rule-based IT assistant. I can help with common issues like password resets, network problems, and software troubleshooting. What seems to be the problem today?",
    "hi": "Hello! I'm a rule-based IT assistant. I can help with common issues like password resets, network problems, and software troubleshooting. What seems to be the problem today?",

    # Intent 6: IT Contact Info
    "technician": "Please contact the IT Helpdesk as extension 4455.",
    "person": "Please contact the IT Helpdesk as extension 4455.",
    "human":"Please contact the IT Helpdesk as extension 4455.",
    "daniel": "Technician Daniel Vincent's extension is 4459.",
    "emergency": "Please contact the IT emergancy cell-phone at 225-867-5309."
}

def chat_bot_response(user_input):
    """
    Analyzes user input against predefined rules and returns a response.
    
    Args:
        user_input (str): The user's typed message.
        
    Returns:
        str: The chatbot's response.
    """
    # Convert input to lowercase to make it case-insensitive
    user_input = user_input.lower()
    
    # Check for specific rules in order of priority.
    # We check for more specific/critical keywords first.
    if "password" in user_input or "login" in user_input or "locked" in user_input or "account" in user_input or "reset" in user_input:
        return rules["password"]
    
    elif "internet" in user_input or "network" in user_input or "wifi" in user_input or "connect" in user_input:
        # A simple response for network issues
        return rules["internet"]
        
    elif "printer" in user_input or "print" in user_input or "scanner" in user_input:
        return rules["printer"]
        
    elif "computer" in user_input or "screen" in user_input:
        return rules["computer"]
        
    elif "software" in user_input or "app" in user_input or "program" in user_input:
        return rules["software"]
    
    elif "technician" in user_input or "person" in user_input or "human" in user_input:
        return rules["technician"]
    
    elif "daniel" in user_input:
        return rules["daniel"]
    
    elif "emergancy" in user_input:
        return rules["emergancy"]

    # This is a fallback for general greetings. This comes last
    # so more specific rules are prioritized.
    elif "hello" in user_input or "hi" in user_input or "help" in user_input:
        return rules["hello"]
        
    # The default response if no keywords are matched
    else:
        return "I'm sorry, I don't understand that request. Could you please rephrase it?"

def main():
    """
    Main function to run the chatbot in a conversational loop.
    """
    print("Welcome to the IT Help Desk Chatbot!")
    print("You can ask me about password issues, network problems, and more.")
    print("Type 'quit' or 'exit' to end the chat.")

    # Start an infinite loop for the conversation
    while True:
        # Get input from the user
        user_input = input("You: ")
        
        # Check for exit commands
        if user_input.lower() in ["quit", "exit"]:
            print("Chatbot: Goodbye!")
            break
            
        # Get and print the chatbot's response
        response = chat_bot_response(user_input)
        print(f"Chatbot: {response}")

if __name__ == "__main__":
    main()
# 2.2 AI: From Talos to Deep Blue
## Part 1: Prompting the AI for Porject Ideas
### User-Facing IT Help Desk Chatbot
This chatbot could handle basic user requests like resetting a password, checking system status, or providing instructions for connecting to the company's Wi-Fi.

Rules:

IF the user's message contains "password" OR "can't log in" THEN prompt them to confirm their username and initiate the password reset process.

IF the user asks "is the server down?" THEN check the server's status using a ping command and respond with "The server is currently online" or "The server appears to be offline."

IF the user asks "how do I connect to Wi-Fi?" THEN provide step-by-step instructions for their operating system (e.g., "Go to Settings -> Network & Internet -> Wi-Fi...").


### IT System Recommendation Engine
This tool could help a small business owner choose an IT setup (e.g., servers, software, security) based on their budget, number of employees, and specific needs.

Rules:

IF the business has <10 employees AND the budget is < $5,000 THEN recommend cloud-based services (e.g., Google Workspace, Microsoft 365) and a basic firewall.

IF the business requires high data security AND has >50 employees THEN recommend an on-premise server, dedicated firewall, and a professional-grade antivirus solution.

IF the business primarily uses graphic design software THEN recommend a high-performance workstation with a dedicated GPU.

### Firewall Rule Management Tool
This system would help an IT technician validate and optimize firewall rules to prevent conflicts and ensure security policies are met.

Rules:

IF a new rule allows a broad range of traffic (ANY source, ANY destination) AND it is placed before a more specific rule that denies the same traffic THEN flag a potential security risk (rule conflict).

IF a rule has not been triggered in 90 days THEN suggest it for review or deletion to simplify the rule set.

IF a rule allows traffic on a known insecure port (e.g., port 23 for Telnet) THEN issue a security warning and recommend using a more secure protocol (e.g., SSH).

### Chosen Project: User-Facing IT Help Desk Chatbot
The help-desk chatbot idea hurts close to home for me because I am currently an IT Support Analyst. With systems evolving on a daily basis, it is difficult to play the role of Technical Support AND System Administrator in my current environment.

## Part 2: 

### Rules and Logic Mapping
Here's a breakdown of common IT help desk issues and the rules you could build to handle them. For each "Intent," your system should check for the associated keywords.

#### 1. Intent: Password & Account Issues

Keywords: password, login, locked, account, reset

Logic:

Check if the user input contains any of these keywords.

Response/Action:

Respond with: "I can help with password issues. Do you need to reset your password or unlock your account?"

Wait for the user's next input and guide them to a specific process (e.g., directing them to a web page or collecting their username for an IT team to follow up).

#### 2. Intent: Network Connectivity Problems

Keywords: internet, network, wifi, can't connect, slow

Logic:

Check if the user input contains any of these keywords.

Response/Action:

Respond with: "Okay, let's troubleshoot your network. Can you tell me if this is affecting a specific website or all of your internet access?"

Provide simple initial steps: "Have you tried restarting your modem and router?"

#### 3. Intent: Printer & Hardware Issues

Keywords: printer, print, scanner, computer, monitor, screen

Logic:

Check for any of these keywords. You may need to create sub-rules for more specific problems (e.g., "printer offline," "paper jam").

Response/Action:

For a general printer query: "I can help with common printer problems. Are you getting an error message? Or is the printer not responding?"

For a hardware issue: "Please restart your device. If the problem persists, please provide the model number of the hardware you are having issues with."

#### 4. Intent: Software/Application Problems

Keywords: software, app, program, crashes, not working

Logic:

Check if the input contains these keywords and then try to identify a specific application if possible (e.g., "Microsoft Word," "Excel").

Response/Action:

"What software are you having trouble with? Can you please describe the issue in a few more words?"

#### 5. Intent: General Help and Greeting

Keywords: hello, hi, help, what can you do, assistance

Logic:

This should be a lower-priority rule, checked only if more specific keywords are not found.

Response/Action:

"Hello! I'm a rule-based IT assistant. I can help with common issues like password resets, network problems, and software troubleshooting. What seems to be the problem today?"

## Part 3: Rules/Logic for the Chosen System

Sammple input and output:

Welcome to the IT Help Desk Chatbot!
You can ask me about password issues, network problems, and more.

You: my screen is black
Vhatbot: Please restart your device. If the problem persists, please provide the model number of the hardware you are having issues with.

You: I need Daniel from IT
Chatbot: Technician Daniel Vincent's extension is 4459.

You: my printer isn't working
Chatbot: I can help with common printer problems. Are you getting an error message? Or is the printer not responding?

## Part 4: Reflection

My rule-based system is a very basic chatbot using if-then statements based on the user's input. It is designed to respond with helpful information, additional questions, and contact numbers for the IT team in case of emergencies. When the user's input contains certain keywords, it will respond with predetermined statements for the user to read. Some of the issues it responds to inlove password and account issues, network connectivity issues, printer and hardware issues, software/applications problems, and IT contact information. I also inclided some general greetings to Follow up question functionality is not currently present but I imagine it would be as easy as a nest if-then state. This system shows the limitation of a rule-based chatbot as it can only imitate a human response in a narrow capacity. Some challenges I noticed when using an LLM to help brainstorm project ideas were duplications in the list of ideas. The duplications were not one-to-one but it some projects were so close in nature they could be built into one system. During the coding process, I only needed to refine the responses and keywords for my particular use. For example, I included our actual extensions and a suggestion to use the SSPR system we have implented at my company. I also tuned the keywords to include words users are more likely to use such as 'screen' vs 'monitor.' Believe it or not, I have users that have never heard the word 'monitor' before. During this assignement I ran into minimal issues. I have, however, run into some halucination and continuity issues in previous priojects that were more complex.
#include <iostream>
#include <string>
using namespace std;

// Chip class definition
class Chip{
    private:
        char chipType;    // Type of the Chip (A: Addition, S: Subtraction, etc.)
        string id;        // Unique identifier for the Chip
        Chip* input1;     // Pointer to the first Input chip
        Chip* input2;     // Pointer to the second Input Chip (can be NULL)
        Chip* output;     // Pointer to the Output Chip (is NULL for output chips)
        double inputValue; // for the Input Chip
        double result;     // Computed result for non-input chips

    public:
        // constructor
        Chip(char type, const string& id);

        // Method prototypes
        void  setInput1(Chip* inputChip);     // Sets the first input chip
        void  setInput2(Chip* inputChip);     // Sets the second input chip (can be NULL)
        void  setOutput(Chip* outputChip);    // Sets the output chip (can be NULL)
        void  compute();    // Performs the operation based on the chip type

        void display() const; // displays the chip's information
          //example: I6, Output = S600 --- for the input Chip
          //example: O50, Input 1 = S600 --- for the output Chip
          //example: A100, Input 1 = I1, Input 2 = I2, Output = M300

        string getId() const;     // returns the chip ID
        char getChipType() const;


        //******** OTHER METHODS AS NECESSARY ***********//
        void setInputValue(double Value);
        Chip* getInput1();
        Chip* getInput2();
        Chip* getOutput();
        //double getInputValue() const;
        double getResult() const;
};

// METHODS DEFINITION FOR THE CHIP CLASS

Chip :: Chip (char type, const string& id) {
    chipType = type;
    this->id = id;
    input1 = nullptr;
    input2 = nullptr;
    output = nullptr;
    inputValue = 0.0;
    result = 0.0;

}

void Chip:: setInput1(Chip* inputChip){
    input1 = inputChip;
}

void Chip:: setInput2(Chip* inputChip){
    input2 = inputChip;
}

void Chip:: setOutput(Chip* outputChip){
    output = outputChip;
}

void Chip:: setInputValue (double value){
    if (chipType == 'I') {
        inputValue = value;
    }
    else {
        std::cout << "Error : Input value can only be set for Input Chips" << endl;
    }
}

void Chip:: compute() {

    if (chipType == 'I') {
        result = inputValue;
        return;
    }
    // to avoid recomputation
    //if (result!= 0) return;

    //compute recursively from inputs
    if (input1) input1->compute();
    if (input2) input2->compute();

    // chip specific computation
    if (chipType == 'A') { // addition chip
    result = input1->getResult() + input2->getResult();
    }
    else if (chipType =='S') { //subtraction chip
    result = input1->getResult() - input2->getResult();
    }
    else if (chipType =='M') { //multiplication chip
    result = input1->getResult() * input2->getResult();
    }
    else if (chipType =='N') { //negation chip
    result = (-1) * input1->getResult();
    }
    else if (chipType =='D') { //division chip
         if (input2->getResult() != 0) {
             result = input1->getResult() / input2->getResult();
         }
         else{
            std::cout  << "Error: Division by zero is not allowed." << endl;
         }
    }
    else if (chipType == 'O') {
        if (input1) {
            result = input1->getResult();
        }
        else {
            cout << "Error: Output chip has no input." << endl;
        }
    }
}

void Chip::display() const {
    if (chipType == 'I'){
        // for input chips: display the input chip with its output connection.
        std::cout << id << ", Output = " << (output ? output->getId() : "None") << std::endl;
    }
    else if (chipType == 'O'){
        // for output chips: Display the output chip with its input connection.
        std::cout << id << ", Input 1 = " << (input1 ? input1->getId() : "None") << std::endl;
    }
    else {
        // for other chips like A(Addition), S (Subtraction), M (Multiplication), N (Negation), D (Division)
        // display both input and output connections
        std::cout << id << ", Input 1 = " << (input1 ? input1->getId() : "None")
                  << ", Input 2 = " << (input2 ? input2->getId() : "None")
                  << ", Output = " << (output ? output->getId() : "None") << std::endl;
    }
}

string Chip::getId() const {
    return id;
} 

char Chip::getChipType() const {
    return  chipType;
}

Chip* Chip::getInput1() {
    return input1; 
}

Chip* Chip::getInput2() {
    return input2;
}

Chip* Chip::getOutput() {
    return output;
}

double Chip::getResult() const {
    return result;
}

int main() {

    // Read the number of chips
    int numChips;
    cin >> numChips;

    // Create an array of chip objects pointers
    Chip** allChips;
    allChips = new Chip* [numChips];

    // Read the chip information and create chip objects
    for (int i = 0; i < numChips; i++) {
        string chipId;
        cin >> chipId;

        char type = chipId[0];
        allChips[i] = new Chip(type, chipId);
    }

    // Read the number of commands
    int numCommands;
    cin >> numCommands;

    // Process the commands
    for  (int i = 0; i < numCommands; i++) {
        char command;
        cin >> command;

        // Connect two chips
        if (command == 'A') { 
            string chipId1;
            string chipId2;
            cin >> chipId1 >> chipId2;

            Chip* chip1 = nullptr;
            Chip* chip2 = nullptr;

            // Find the chip objects
            for(int j = 0; j < numChips; j++){
                if(allChips[j]->getId() == chipId1) chip1 = allChips[j];
                if(allChips[j]->getId() == chipId2) chip2 = allChips[j];
            }

            // Connect the chips
            if (chip2->getChipType() == 'N' || chip2->getChipType() == 'O'){
                chip2->setInput1(chip1);
                chip1->setOutput(chip2);  // Set the output chip for chip1
            }
            else if (chip2->getChipType() == 'A' || chip2->getChipType() == 'S' || chip2->getChipType() == 'M' || chip2->getChipType() == 'D') {
                if ((chip2->getInput1() == nullptr)){
                    chip2->setInput1(chip1);
                }
                else {
                    chip2->setInput2(chip1);
                }
                chip1->setOutput(chip2); // set the output chip for chip1
            }
        
        }

        // Set an input value for an input chip
        else if (command == 'I') {
                string chipId;
                double value;
                cin >> chipId >> value;

                for (int j = 0; j < numChips; j++) {
                    if (allChips[j]->getId() == chipId) {
                        allChips[j]->setInputValue(value);
                        break;
                    }
                }
            }

        // Compute the output of a chip
        else if (command == 'O'){
             string outputChipId;
             cin  >> outputChipId;

             cout << "Computation Starts" << endl;
             for (int j = 0; j < numChips; j++) {
                 if(allChips[j]->getId() == outputChipId){
                     allChips[j]->compute();
                     cout << "The output value from this circuit is " << allChips[j]->getResult() << endl;
                     break;
                 } 
             }
        }
    }

    // Display the connections
    std::cout << "***** Showing the connections that were established" << endl;
    for (int i = 0; i < numChips; i++) {
        if (allChips[i]->getChipType() =='I'){
            allChips[i]->display();
        }
    }

    for (int i = 0; i < numChips; i++) {
        if  (allChips[i]->getChipType() != 'I' && allChips[i]-> getChipType() != 'O'){
            allChips[i]->display();
        }

    }

    for (int i = 0; i < numChips; i++) {
        if (allChips[i]->getChipType() == 'O'){
            allChips[i]->display();
        }
    }


    // Delete dynamically allocated memory
    for (int i = 0; i < numChips; i++) {
        delete allChips[i];
    }
    delete[] allChips;
    return 0; 
}

// The process of connections made by the chips in the program:
// 1. The program reads the number of chips and creates an array of chip objects pointers.
// 2. The program reads the chip information and creates chip objects.
// 3. The program reads the number of commands and processes each command.
// 4. For each command, the program connects two chips or sets an input value for an input chip.
// 5. When a chip is connected to another chip, the program sets the input and output pointers accordingly.
// 6. When an input value is set for an input chip, the program updates the input value of the chip.
// 7. When a chip is asked to compute its output, the program recursively computes the output of the chip and its inputs.
// 8. Finally, the program displays the connections established between the chips.

/**
 Questions a asked to programming tools to help debug and build the program efficiently:
 * 
 * 1. How do I create a new chip object and add it to the array of chip objects?
 * 2. How do I connect two chips together?
 * 3. How do I set an input value for an input chip?
 * 4. How do I compute the output of a chip?
 * 5. How do I display the connections established between the chips?
 * 6. What is the purpose of the compute method in the Chip class?
 * 7. How do I handle division by zero in the division chip?
 * 8. How do I prevent recomputation of the output of a chip?
 * 9. How do I handle the case where an output chip has no input?
 * 10. How do I handle the case where an input chip has no output?
 * 11. How do I display the chip's information in the display method?
 * 12. How do I set the input and output pointers when connecting two chips?
 * 13. How do I update the input value of a chip when setting an input value?
 * 14. How do I recursively compute the output of a chip and its inputs?
 * 15. How do I handle the case where a chip has multiple inputs?
 * 16. How do I handle the case where a chip has multiple outputs?
 * 17. How do I prevent memory leaks when deleting dynamically allocated memory?
 * 18. How do I handle the case where the number of commands is zero?
 * 19. How do I handle the case where the number of chips is zero?
 * 20. How do I optimize the program for performance?
 * 
 * 
 * 
 * The questions I asked to the programming tool played a crucial role in understanding the program's logic and execution.
 * By asking questions such as "How do I create a new chip object and add it to the array of chip objects?"
 * and "How do I connect two chips together?", I was able to grasp the fundamental concepts of the program,
 * including the creation of chip objects and the establishment of connections between them.
 * The questions also helped me to understand the purpose of specific methods, such as the compute method in the Chip class,
 * and how to handle edge cases, such as division by zero and recomputation of output values.
 * Additionally, the questions enabled me to identify potential issues, such as memory leaks and handling of multiple inputs
 * and outputs, and to develop strategies for optimizing the program's performance. By working through these questions,
 * I gained a deeper understanding of the program's execution and was able to debug and improve the code,
 * ultimately leading to a more efficient and effective program. The questions also helped me to think critically and
 * develop problem-solving skills, which are essential for programming and software development.
 * 
 */
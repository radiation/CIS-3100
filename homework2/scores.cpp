/*
This is a VERY clunky way of doing this, but I followed the directions as written. If I were to write this from scratch based on the 
outcome we want, I would create a vector of Student objects, which contains the id, exam scores, and weighted average. We'd then be 
able to just iterate through that vector at any time and pull the scores we want, and we'd be able to tie the student to their
scores and weighted average. This would also allow us to easily sort the students by their weighted average, which would be useful
if we wanted to print out the students in order. I also used a CSV instead of just a space-delimited file, which is why I had to
parse the CSV. If we were to use a space-delimited file, we could just use the extraction operator to read the data, but CSVs are 
what you would get in the real world.
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
using namespace std;

// Prototypes
int read_arrays(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int num_students);
void print_array(int scores[], int size, string title, ofstream& outFile);
void make_weighted_avg(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int weighted_avgs[], int num_students);
void find_smallest_and_pos(int nums[], int k, int &smallest, int &pos);

// Globally-scoped filenames (or paths if needed)
string input_file = "scores.csv", output_file = "output.txt";


int main() {

    // Define the arrays; we have num_students as a parameter in case we need to change it, populate it dynamically from the file
    // length, or if we want to prompt the user to tell us how many scores to read.
    const int num_students = 40;
    int exam_one_scores[num_students], exam_two_scores[num_students], exam_three_scores[num_students], weighted_avgs[num_students];

    // Read the arrays from the file; if there's an error, return 1
    if (read_arrays(exam_one_scores, exam_two_scores, exam_three_scores, num_students)) {
        cerr << "Error reading arrays from file." << endl;
        return 1;
    }

    // Calculate the weighted averages (we're using ints to simplify the output, but you could use doubles if you want more precision)
    make_weighted_avg(exam_one_scores, exam_two_scores, exam_three_scores, weighted_avgs, num_students);

    /*
    Open the output file. We're opening it in main and passing it as a param so we only need to open and close it once, instead of 
    repeatedly. If we had hundreds of sets of data to write, this way would be much more efficient. Also this makes it easy to abort if 
    we can't open the file.
    */
    ofstream outfile(output_file);

    if (!outfile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    // Print the arrays
    print_array(exam_one_scores, num_students, "Exam 1 Scores: ", outfile);  
    print_array(exam_two_scores, num_students, "Exam 2 Scores: ", outfile);
    print_array(exam_three_scores, num_students, "Exam 3 Scores: ", outfile);
    print_array(weighted_avgs, num_students, "Weighted Averages: ", outfile);

    // Find the smallest exam score and its position
    int smallest, pos;
    find_smallest_and_pos(exam_one_scores, num_students, smallest, pos);
    cout << "The smallest exam 1 score is " << smallest << " at position " << pos << endl;
    outfile << "The smallest exam 1 score is " << smallest << " at position " << pos << endl;
    find_smallest_and_pos(exam_two_scores, num_students, smallest, pos);
    cout << "The smallest exam 2 score is " << smallest << " at position " << pos << endl;
    outfile << "The smallest exam 2 score is " << smallest << " at position " << pos << endl;
    find_smallest_and_pos(exam_three_scores, num_students, smallest, pos);
    cout << "The smallest exam 3 score is " << smallest << " at position " << pos << endl;
    outfile << "The smallest exam 3 score is " << smallest << " at position " << pos << endl;

    // Close the file
    outfile.close();

    return 0;

}

/*
Read the data from the file. We have this function set to return an errror code if the file can't be opened. This is a good practice
because it allows us to handle the error in main, where we can decide what to do if the file can't be opened. In this case, we're
just returning an error code, but we could also prompt the user for a new filename, or we could just exit the program.
This function takes the three exam score arrays and the number of students as parameters. We could also adjust this to take a vector
of arrays if the number of exams is dynamic, or if we wanted to read an arbitrary number of exams from the file.
*/
int read_arrays(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int num_students) {

    string item, line;
    int pos, cur_student = 0;

    // Open the file
    ifstream file(input_file);

    // Check if the file is open
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Skip the header line if your CSV has headers
    getline(file, line);

    // Iterate through the subsequent lines
    while (getline(file, line)) {

        // Create a stringstream to parse the line, again, because we're using a CSV
        stringstream ss(line);
        string item;
        int i = 0;

        // Iterate through the comma-separated values
        while (getline(ss, item, ',')) {
            switch (i) {
                case 0:
                    // Handle student ID or ignore if not needed
                    break;
                case 1:
                    exam_one_scores[cur_student] = stoi(item);
                    break;
                case 2:
                    exam_two_scores[cur_student] = stoi(item);
                    break;
                case 3:
                    exam_three_scores[cur_student] = stoi(item);
                    break;
            }
            i++;
        }
        cur_student++;
    }

    // Close the file
    file.close();

    return 0;

}

/*
This function prints an array of integers to the console and to a file. We're using a reference to an ofstream so we can write to the
file that was opened in main. This function takes the array, the number of elements in the array, a title for the output, and the
output file stream as parameters.
*/
void print_array(int nums[], int k, string title, ofstream& outfile) {

    // Print the title
    cout << title << endl;
    outfile << title << endl;

    // Print the scores. We're using left/right from iomanip to make the output look nice
    for (int i=0; i<k; i++) {
        cout << right << setw(10) << nums[i];
        outfile << right << setw(10) << nums[i];
        if ((i+1) % 6 == 0) {
            cout << endl;
            outfile << endl;
        }
    }

    cout << endl << endl;
    outfile << endl << endl;

}

// This function calculates the weighted average for each student from the three exam arrays and puts it into the weighted_avgs array
void make_weighted_avg(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int weighted_avgs[], int num_students) {
    for (int i=0; i<num_students; i++) {
        weighted_avgs[i] = (
                            (exam_one_scores[i]   * 1) + 
                            (exam_two_scores[i]   * 2) + 
                            (exam_three_scores[i] * 3)
                           ) / 6;
    }
}

// This function finds the smallest number in an array and its position; it takes the array, the number of elements in the array, and
// references to the smallest number and its position as parameters
void find_smallest_and_pos(int nums[], int k, int &smallest, int &pos) {
    smallest = nums[0];
    pos = 0;
    for (int i=1; i<k; i++) {
        if (nums[i] < smallest) {
            smallest = nums[i];
            pos = i;
        }
    }
}
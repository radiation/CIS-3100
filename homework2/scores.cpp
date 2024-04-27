/*
This is a VERY clunky way of doing this, but I followed the directions as written. If I were to write this from scratch based on the 
outcome we want, I would create a vector of Student objects, which contains the id, exam scores, and weighted average. We'd then be 
able to just iterate through that vector at any time and pull the scores we want, and we'd be able to tie the student to their
scores and weighted average. This would also allow us to easily sort the students by their weighted average, which would be useful
if we wanted to print out the students in order.
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

// Prototypes
int read_arrays(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int num_students);
void print_array(int scores[], int size);
void make_weighted_avg(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int weighted_avgs[], int num_students);
void find_smallest_and_pos();

int main() {

    // Filenames
    string input_file = "scores.csv", output_file = "weighted_avg.csv";

    // Define the arrays
    const int num_students = 40;
    int exam_one_scores[num_students], exam_two_scores[num_students], exam_three_scores[num_students];

    // Read the arrays from the file
    read_arrays(exam_one_scores, exam_two_scores, exam_three_scores, num_students);

    // Print the arrays
    cout << "Exam 1 scores:" << endl;
    print_array(exam_one_scores, num_students);
    cout << "Exam 2 scores:" << endl;
    print_array(exam_two_scores, num_students);
    cout << "Exam 3 scores:" << endl;
    print_array(exam_three_scores, num_students);
    return 0;

}

int read_arrays(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int num_students) {

    string item, line;
    int pos, cur_student = 0;

    // Open the file
    ifstream file("scores.csv");

    // Check if the file is open
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Skip the header line if your CSV has headers
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);
        string item;
        int i = 0;

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

void print_array(int nums[], int k) {
    for (int i=0; i<k; i++) {
        cout << right << setw(10) << nums[i];
        if ((i+1) % 6 == 0)
            cout << endl;
    }
    cout << endl;
}

void make_weighted_avg(int exam_one_scores[], int exam_two_scores[], int exam_three_scores[], int weighted_avgs[], int num_students) {
    for (int i=0; i<num_students; i++) {
        weighted_avgs[i] = (exam_one_scores[i] + (exam_two_scores[i]*2) + (exam_three_scores[i]*3)) / 6;
    }
}
#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;


vector< vector<string> > mess_record; //vector declarion. all data will be stored in this vector (mess_record)

void read_file(string fname) //framework
{
    string word, line;
    fstream file(fname, ios::in);
    vector<string> row_data; //stores 1 student's data seperately
    while (getline(file, line))
    {
        stringstream row(line);
        while (getline(row, word, ','))
        {
            row_data.push_back(word); //storing data in vector
        }
        mess_record.push_back(row_data);
        row_data.clear(); //clear row for next entry
    }
}

void vect_sort() //bubble sort ka code
{
    int len = mess_record.size();
    for (int k = 1; k < len - 1; k++) 
    {
        for (int t = 1; t < len - k; t++)
        {
            int curr = stoi(mess_record[t][0]);
            int nxt = stoi(mess_record[t + 1][0]);
            if (curr > nxt) 
            {
                vector<string> tmp = mess_record[t+1];
                mess_record[t + 1] = mess_record[t];
                mess_record[t] = tmp;   
            }
        }
    }
}

bool chk(string regno)
{
    int len = mess_record.size();
    for (int i = 1; i < len; i++)
    {
        if (regno == mess_record[i][0]) //to check if the reg already exists in mess_record
        {
            return false;
        }
    }
    return true;
}

void reg() //to register
{
    string regno, name;
    cout << "Enter your registration number: ";
    cin >> regno;
    cout << endl;

    cout << "Enter your name: ";
    cin >> name;
    cout << endl;

    if (chk(regno))
    {
        vector <string> tmp{ regno, name, "0", "Out", "0" };
        mess_record.push_back(tmp);
        vect_sort();
        cout << "Operation Successful!" << endl;
    }
    else
    {
        cout << "Student already registered" << endl;
    }
}

int getidx(string regno)
{
    int len = mess_record.size();
    for (int i = 1; i < len; i++)
    {
        if (regno == mess_record[i][0])
        {
            return i;
        }
    }
    return -1;
}

void search()
{
    string regno;

    cout << "Enter your registration number: ";
    cin >> regno;
    cout << endl;

    int index = getidx(regno);
    if (index == -1)
    {
        char ch;
        cout << "Student not found. Do you want to register them? (y/n): ";
        cin >> ch;
        cout << endl;
        if (ch == 'y')
        {
            reg();
        }
        else
        {
            cout << "Operation Successful!" << endl;
        }

    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            cout << mess_record[index][i] << " ";
        }
        cout << endl;
        cout << "Operation Successful!" << endl;
    }
}

void status()
{
    string regno;

    cout << "Enter your registration number: ";
    cin >> regno;
    cout << endl;

    int index = getidx(regno);

    if (index == -1)
    {
        char ch;
        cout << "Student not found. Do you want to register them? (y/n): ";
        cin >> ch;
        cout << endl;
        if (ch == 'y')
        {
            reg();
        }
        else
        {
            cout << "Operation Successful!" << endl;
        }

    }
    else
    {
        char ch;
        cout << "Status = " << mess_record[index][3] << endl; // 3 ma save hoga 
        cout << "Do you want to change status? (y/n): ";
        cin >> ch;
        cout << endl;
        if (ch == 'y')
        {
            if (mess_record[index][3] == "In")
            {
                mess_record[index][3] = "Out";
            }
            else
            {
                mess_record[index][3] = "In";
                mess_record[index][4] = to_string(stoi(mess_record[index][4]) + 1); 
            }
        }
        else
        {
            cout << "Operation Successful!" << endl;
        }
    }

}

void del()
{
    string regno;

    cout << "Enter your registration number: ";
    cin >> regno;
    cout << endl;

    int index = getidx(regno);

    if (index == -1)
    {
        cout << "Student not registered." << endl;
    }
    else
    {
        mess_record[index] = mess_record.back(); //index push 
        mess_record.pop_back(); //
        vect_sort();
        cout << "Operation Successful!" << endl;
    }
}

void totalstatus()
{
    char ch;

    cout << "Do you want to know total number of 'In' Students? (y/n): ";
    cin >> ch;
    cout << endl;

    if (ch == 'y')
    {
        int count = 0;
        for (int i = 1; i < mess_record.size(); i++)
        {
            if (mess_record[i][3] == "In")
            {
                count += 1;
            }
        }
        cout << "Total number of 'In' students: " << count << endl;
    }

    cout << "Do you want to know total number of 'Out' Students? (y/n): ";
    cin >> ch;
    cout << endl;

    if (ch == 'y')
    {
        int count = 0;
        for (int i = 1; i < mess_record.size(); i++)
        {
            if (mess_record[i][3] == "Out")
            {
                count += 1;
            }
        }
        cout << "Total number of 'Out' students: " << count << endl;
    }

    cout << "Operation Successful!" << endl;

}

void bill()
{
    for (int i = 1; i < mess_record.size(); i++)
    {
        mess_record[i][2] = to_string(300 * stoi(mess_record[i][4]));
    }
    cout << "Operation Successful!" << endl;
}

int main()
{
    string fname = "data.csv";

        
        read_file(fname); //file data.csv is being read into the 2d vector mess_record
        int choice;
        
        cout << "*********************************" << endl;
        cout << "WELCOME TO MESS MANAGEMENT SYSTEM" << endl;
        cout << "*********************************" << endl << endl;
        do
        {
            cout << endl;
            cout << "                 MENU                    " << endl;
            cout << "The following functions can be performed: " << endl;
            cout << "1) Register new student" << endl;
            cout << "2) Search student record" << endl;
            cout << "3) Change mess status ('In/Out')" << endl;
            cout << "4) Delete record" << endl;
            cout << "5) Show the total number of 'In/Out' students" << endl;
            cout << "6) Calculate bill" << endl;
            cout << "0) Exit" << endl;
            cout << endl;
            cout << "Please enter the function you wish to perform: ";
            cin >> choice;
            cout << endl;

            switch (choice)
            {
            case 1:
                reg();
                break;
            case 2:
                search();
                break;
            case 3:
                status();
                break;
            case 4:
                del();
                break;
            case 5:
                totalstatus();
                break;
            case 6:
                bill();
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << "Incorrect Operation!" << endl;
                break;
            }
        } while (choice != 0);

        vect_sort();

        fstream ofile(fname, ios::out);
        for (int i = 0; i < mess_record.size() - 1; i++)
        {
            ofile << mess_record[i][0] << "," << mess_record[i][1] << "," << mess_record[i][2] << "," << mess_record[i][3] << "," << mess_record[i][4] << "\n";
        }
        int i = mess_record.size() - 1;
        ofile << mess_record[i][0] << "," << mess_record[i][1] << "," << mess_record[i][2] << "," << mess_record[i][3] << "," << mess_record[i][4];
}
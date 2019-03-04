#include <iostream>
#include <vector>

using namespace std;

// class to define all the elements of the Matrix (sparseRowIndexes and value)

template<class DT>
class SparseRow {
    template<class DS>
    friend ostream &operator << (ostream& output,SparseRow<DS>& M);// Overloading the operator of the class SparseRow
protected:
    int row;//Row#
    int col;//Column#
    DT value;//We will assume that all our values will be integers
    int sparseRowIndex;//index of the sparseRow 
public:
    SparseRow (); //default constructor;row=-1;col=-1;value=0
    SparseRow(int i, int r, int c, DT v); 
    virtual ~SparseRow(); //destructor
    int getRow(); //Method to get the row
    void setRow(int r); //Method to get set the row
    int getCol(); //Method to get the column
    void setCol(int c); //Method to get set the column
    DT getSparseVal(); //Method to get the value of the SparseRow value 
    void setSparseVal(DT v); //Method to set the value of the SparseRow value
    int getInd(); //Method to get the Index of this SparseRow
    void setInd(int i); //Method to set the Index i of this SparseRow
};

//Class to define the maytrix structure and elemenets

template <class DT>
class SparseMatrix {
    template<class DS>
    friend ostream &operator << (ostream& output,SparseMatrix<DS>& M);//Overloading the operator of the class SparseMatrix
protected:
    int noRows; //Number of rows of the original matrix
    int noCols; //Number of columns of the original matrix
    DT commonValues; //Number of comon values
    int nonCommonValues; //Number of non comon values
    vector<SparseRow<DT>>* myMatrix; //Dynamic Array of SparseRows containin the non comon values
public:
	SparseMatrix();
    SparseMatrix (int n, int m, DT cv); //Constructor to initialize the SparseMatrix
    virtual ~SparseMatrix(); //destructor 
    SparseMatrix *operator! (); //Method to Transposes the matrix
    SparseMatrix *operator* (SparseMatrix<DT>& M); //Multiplication
    SparseMatrix *operator+ (SparseMatrix<DT>& M); //Addition
    void displayMatrix (); //Display the matrix in its original format
    void setSparseRow(int sparseRowIndex, int r, int c, DT v); //Method to set the row of the SparseMatrix
    SparseRow<DT> getSparseRow(int c); //Method to return the SparseRow in the SparseMatrix column
    bool isNonSparse(int r, int c);// Methos to check if the nonSparse element exixts
    SparseRow<DT> getSparseRow(int r, int c); ////Method to return the SparseRow in the SparseMatrix row and column
};

//Regular constructor of the SparseRow class
template<class DT>
SparseRow<DT>::SparseRow(int i, int r, int c, DT v) {
    this->setCol(c);
    this->setRow(r);
    this->setSparseVal(v);
    this->setInd(i);
};

//SparseRow default Constructor when it is no initialized
template <class DT>
SparseRow<DT>::SparseRow() {
    this->setCol(-1);
    this->setRow(-1);
    this->setSparseVal(0);
    this->setInd(NULL);
};

//constructor to initialize the SparseMatrix class
template <class DT>
SparseMatrix<DT>::SparseMatrix (int n, int m, DT cv) {
    noRows = n;
    noCols = m;
    commonValues = cv;
    myMatrix = new vector<SparseRow<DT>>();
    nonCommonValues = NULL;
};

//SparseMatrix default Constructor when it is no initialized
template <class DT>
SparseMatrix<DT>::SparseMatrix () {
    noRows = 0;
    noCols = 0;
    commonValues = 0;
    nonCommonValues = NULL;
};

//destruct the sparseRow
template <class DT>
SparseRow<DT>::~SparseRow() {

};

//destruct the sparseMatrix
template <class DT>
SparseMatrix<DT>::~SparseMatrix() {

};

//get the sparseRow in the sparseMatrix
template <class DT>
SparseRow<DT> SparseMatrix<DT>::getSparseRow(int c) {
    return (*myMatrix)[c];
};

//get the sparseRow in the sparseMatrix at the row c and column c
template <class DT>
SparseRow<DT> SparseMatrix<DT>::getSparseRow(int r, int c) {
    for (int i = 0; i < (*myMatrix).size(); i++) {
        if ((*myMatrix)[i].getCol() == c && (*myMatrix)[i].getRow() == r) {
            return (*myMatrix)[i];
        }
    }
    cout << "Row " << r << "and Column " << c << " Not found!"<< endl;
    return SparseRow<DT>();
};

//Get the row
template <class DT>
int SparseRow<DT>::getRow() {
    return row;
};

//Get the column 
template <class DT>
int SparseRow<DT>::getCol() {
    return col;
};

//get the value from this SparseRow
template <class DT>
DT SparseRow<DT>::getSparseVal() {
    return value;
};

//get the sparseRowIndex
template <class DT>
int SparseRow<DT>::getInd() {
    return sparseRowIndex;
};

//Set the sparseRow of the SparseMatrix
template <class DT>
void SparseMatrix<DT>::setSparseRow(int sparseRowIndex, int r, int c, DT v) {
    (*myMatrix).push_back(SparseRow<DT>(sparseRowIndex,r,c,v));
};

//Set the value of the SparseRow
template <class DT>
void SparseRow<DT>::setSparseVal(DT v) {
    this->value = v;
};

//Set the row of the SparseRow
template <class DT>
void SparseRow<DT>::setRow(int r) {
    this->row = r;
};

//Set the column of the SparseRow
template <class DT>
void SparseRow<DT>::setCol(int c) {
    this->col = c;
};

//Set the sparseRowIndex of the SparseRow
template <class DT>
void SparseRow<DT>::setInd(int i) {
    this->sparseRowIndex = i;
};

// Check if it is a sparse value
template <class DT>
bool SparseMatrix<DT>::isNonSparse(int r, int c) {
    for (int i = 0; i < (*myMatrix).size(); i++) {
        if (this->getSparseRow(i).getRow() == r && this->getSparseRow(i).getCol() == c) {
            return true;
        }
    }
    return false;
};
//---------------------------
//class for the defaukt exception
class AddException : public exception {

};

//multiply exception
class ExceptionMultiply : public exception {

};

//exception for addition
class ExceptionCV : public exception {

};

//display the matrix in the normal format
template <class DT>
void SparseMatrix<DT>::displayMatrix() {

    //current row and col
    int currentRow = 0;
    int currentCol = 0;

    //loop the matrix
    for (int i = 0; i < ((noRows)*(noCols)); i++) {

        if (isNonSparse(currentRow, currentCol)) { // if it is non sparse

            cout << getSparseRow(currentRow,currentCol).getSparseVal();// print the value
        }
        //otherwise, print the common value
        else {
            cout << commonValues;
        }

        if (currentCol < noCols) {
            cout << " ";
            currentCol++;
        }
        if (currentCol >= noCols) {
            cout << endl;
            currentCol = 0;
            currentRow++;
        }
    }
};

//displays the sparseRow and go to the line 
template <class DS>
ostream &operator << (ostream &output, SparseRow<DS> &M) {
    output << M.getRow() << " " << M.getCol() << " " << M.getSparseVal() << endl;
    return output;
};

//transposes the matrix
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator!() {

    //stores the temporary row, column and value inside of each iteration of the for loop below
    int r, c;
    DT v;

    //temp SparseMatrix object for return
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValues);


    //main for loop of this function. loops through all of the values in myMatrix and switches the row and column value
    for (int i = 0; i < (*myMatrix).size(); i++) {
        r = (*myMatrix)[i].getRow();
        c = (*myMatrix)[i].getCol();
        v = (*myMatrix)[i].getSparseVal();
        copy->setSparseRow(i, c, r, v);
    }
    //returning the copy that has the switched row and column values
    return copy;
};

//multiplies two matrices together
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator*(SparseMatrix<DT> &M) {

    //checking that the number of columns in the first matrix matches the number of rows in the second matrix
    if (this->noCols != M.noRows) {
        throw ExceptionMultiply();
    }
    if (this->commonValues != M.commonValues) {
        throw ExceptionCV();
    }

    //the SparseMatrix to be returned
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValues);

    //instantiating some variables
    int firstOneRow, firstOneCol, secondOneRow, secondOneCol, sparseRowIndex;
    DT current, firstOneValue,secondOneValue;

    //stores the current row and column values that will be incremented appropriately
    firstOneRow = 0;
    firstOneCol = 0;
    secondOneRow = 0;
    secondOneCol = 0;

    //the sum of the current rows we are multiplying together
    current = 0;

    //the sparseRowIndex of the sum we will be inserting into the copy
    sparseRowIndex = 0;

    //main for loop goes through this process noRows*noCols times
    for (int i = 0; i < ((noRows)*(noCols)); i++) {

        //checking to see if i is 0 and if the matrix's side is 2 or less. required step in order to run properly on small matrices
        if (((noRows > 2) || (noCols > 2)) && (i == 0)) {
            i++;
        }

        //loops through the current rows
        while (firstOneCol < noCols && secondOneRow < noRows) {

            //if theres a non sparse variable at both current row and column values
            if (this->isNonSparse(firstOneRow, firstOneCol)
                && M.isNonSparse(secondOneRow, secondOneCol)) {

                //then sum them up!
                firstOneValue = this->getSparseRow(firstOneRow,firstOneCol).getSparseVal();
                secondOneValue = M.getSparseRow(secondOneRow,secondOneCol).getSparseVal();
                current += (firstOneValue * secondOneValue);
            }

            //incrementing the rows and columns appropriately
            firstOneCol++;
            secondOneRow++;
        }

        //checking to see if anything was added up and adding it to copy if so
        if (current != 0) {
            copy->myMatrix->push_back(SparseRow<DT>(i, firstOneRow, secondOneCol, current));

            //also incrementing the sparseRowIndex and resetting current
            sparseRowIndex++;
            current = 0;
        }

        //checks for end of row/end of column
        if (secondOneCol < M.noCols) {
            firstOneCol = 0;
            secondOneRow = 0;
            secondOneCol++;
            if (secondOneCol >= M.noCols) {
                firstOneRow++;
                secondOneCol = 0;
            }
        }
    }

    //returning
    return copy;
};

//adds two matrices together
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator+(SparseMatrix<DT> &M) {

    //checking that the number of rows and columns match before we start adding
    if ((this->noRows != M.noRows) || (this->noCols != M.noCols)) {
        throw AddException();
    }
    if (this->commonValues != M.commonValues) {
        throw ExceptionCV();
    }

    //creating a copy of the array
    SparseMatrix* copy = new SparseMatrix(noRows,noCols,commonValues);

    //the current row and col
    int currentRow = 0;
    int currentCol = 0;
    int sparseRowIndex = 0;

    for (int i = 0; i < noCols*noRows; i++) {
        DT sum = 0;
        if (this->isNonSparse(currentRow, currentCol)) {
            sum += this->getSparseRow(currentRow, currentCol).getSparseVal();
        }
        if (M.isNonSparse(currentRow, currentCol)) {
            sum += M.getSparseRow(currentRow, currentCol).getSparseVal();
        }
        if (sum != commonValues) {
            copy->myMatrix->push_back(SparseRow<DT>(sparseRowIndex,currentRow,currentCol,sum));
            sparseRowIndex++;
        }

        //end of row/col checks
        if (currentCol < noCols) {
            currentCol++;
        }
        if (currentCol >= noCols) {
            currentCol = 0;
            currentRow++;
        }
    }


    //returning the copy
    return copy;
};

//display the sparse matrix in the normal format
template <class DS>
ostream& operator << (ostream& output, SparseMatrix<DS> &M) {

    for (int i = 0; i < M.myMatrix->size(); i++) {
        output << M.myMatrix->at(i);
    }
    return output;
};

int main ()
{
    //initializing some variables before we use them
    int n, m, cv, sparseRowIndex, value;
    SparseMatrix<int>* temp;

    //reset sparseRowIndex to 0
    sparseRowIndex = 0;

    //prompts the user for input. the program needs the number of rows and columns, the common value and the number of non sparse values
    cin >> n >> m >> cv;
    //initializing the first SparseMatrix with the values entered by the user
    SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);

    //this nested loop takes the input from the user and automatically assigns the row and column value of each
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            //taking input from the user
            cin >> value;

            //check to see if the input value is a common value or not
            if (value != cv) {

                //and if not then we add it to myMatrix and incremement which sparseRowIndex that SparseRow is at
                (*firstOne).setSparseRow(sparseRowIndex,i,j,value);
                sparseRowIndex++;
            }
        }
    }    //this process is exactly the same as the first one. please refer to the comments above
    cin >> n >> m >> cv;
    sparseRowIndex = 0;

    SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            if (value != cv) {
                (*secondOne).setSparseRow(sparseRowIndex,i,j,value);
                sparseRowIndex++;
            }
        }
    }

    //Statements to manipulate and print matrices
    cout << "First one in sparse matrix format" << endl;
    cout << (*firstOne);
    cout << "First one in normal matrix format" << endl;
    (*firstOne).displayMatrix();
    cout << "Second one in sparse matrix format" << endl;
    cout << (*secondOne);
    cout << "Second one in normal matrix format" << endl;
    (*secondOne).displayMatrix();
    cout << "After Transpose first one in normal format" << endl;
    temp = !*firstOne;
    (*temp).displayMatrix();
    cout << "After Transpose second one in normal format" << endl;
    temp = !*secondOne;
    (*temp).displayMatrix();
    cout << "Multiplication of matrices in sparse matrix form:" << endl;
    temp = *secondOne * *firstOne;
    cout << (*temp);
    cout << "Addition of matrices in sparse matrix form:" << endl;
    temp = *secondOne + *firstOne;
    cout << (*temp);
	delete firstOne; //delete the object firstOne
	delete secondOne; //delete the object secondOne
    return 0;
}

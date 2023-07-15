#include <iostream>
#include <vector>
#include <limits>
using namespace std; 

class ShapeCal {
public:
    void run() {
        int numShapes = getNumShapes();  // 도형의 개수를 입력받는 함수 호출
        inputShapes(numShapes);  // 도형들의 정보를 입력받는 함수 호출
        calDulraes();  // 도형의 둘레를 계산하는 함수 호출
        printResult();  // 결과를 출력하는 함수 호출
    }

private:
    struct Shape {
        int type; // 도형의 종류를 나타내는 변수
        vector<double> lengths; // 도형의 변 길이를 저장하는 벡터
        double dulrae;
    };

    vector<Shape> shapes;  // 도형들을 저장하는 벡터

    int getNumShapes() {
        int numShapes;
        while (true) {
            cout << "도형의 개수를 입력하세요 (0을 입력하면 종료): ";
            cin >> numShapes;

            // 입력된 도형의 개수가 0 이상인지 확인합니다.
            if (numShapes >= 0) {
                break;  // 올바른 갑시 입력된 경우 반복문을 종료합니다.
            } else {
                cout << "오류: 도형의 개수는 0 이상이어야 합니다." << endl;
            }
        }
        return numShapes;
    }

    int getShapeType() {
        int shapeType;
        while (true) {
            cout << "도형의 종류를 입력하세요 (1: 원, 2: 직사각형, 3: 삼각형): ";
            cin >> shapeType;

            // 입력된 도형의 종류가 1에서 3 사이인지 확인합니다.
            if (shapeType >= 1 && shapeType <= 3) {
                break;  // 올바른 값이 입력된 경우 반복문을 종료합니다
            } else {
                cout << "오류: 1에서 3 사이의 값을 입력해주세요." << endl;
            }
        }
        return shapeType;
    }


    vector<double> getShapeLengths(int shapeType) {
        int numLengths;
        switch (shapeType) {
            case 1: // 원
                numLengths = 1;
                break;
            case 2: // 직사각형
                numLengths = 2;
                break;
            case 3: // 삼각형
                numLengths = 3;
                break;
        }

        vector<double> lengths(numLengths);
        for (int i = 0; i < numLengths; ++i) {
            cout << "길이 #" << (i + 1) << ": ";
            cin >> lengths[i];
        }
        return lengths;
    }

    bool isTriangle(const vector<double>& lengths) {
        double maxDulrae = numeric_limits<double>::min();
        double sumLengths = 0.0;

        // 주어진 길이 중 가장 긴 길이와 길이의 합을 계산합 
        for (vector<double>::const_iterator it = lengths.begin(); it != lengths.end(); ++it) {
            double length = *it;
            maxDulrae = max(maxDulrae, length);
            sumLengths += length;
        }

        // 삼각형이 되는 조건 확인
        return (maxDulrae < sumLengths - maxDulrae);
    }

    void inputShapes(int numShapes) {
        for (int i = 0; i < numShapes; ++i) {
            Shape shape;
            shape.type = getShapeType();
            shape.lengths = getShapeLengths(shape.type);

            // 삼각형인 경우 조건 검사
            if (shape.type == 3 && !isTriangle(shape.lengths)) {
                cout << "오류: 삼각형이 아닌 길이입니다. 다시 입력해주세요." << endl;
                --i;  // 다시 입력 받기 위해 i를 감소시킴
                continue;
            }

            shapes.push_back(shape);
        }
    }

    void calDulraes() {
        for (vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            Shape& shape = *it;
            double dulrae = 0.0;

            switch (shape.type) {
                case 1: // 원
                    dulrae = 2 * 3.14159 * shape.lengths[0];
                    break;
                case 2: // 직사각형
                    dulrae = 2 * (shape.lengths[0] + shape.lengths[1]);
                    break;
                case 3: // 삼각형
                    dulrae = shape.lengths[0] + shape.lengths[1] + shape.lengths[2];
                    break;
            }

            shape.dulrae = dulrae;
        }
    }

    void printResult() { // 도형들을 순회하면서 정보를 출력합니다
        for (vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it) { 
            const Shape& shape = *it; // 현재 도형에 대한 레퍼런스를 가져옵니다.
            string shapeName;
            switch (shape.type) { // 도형의 종류에 따라 이름을 설정합니다.
                case 1:
                    shapeName = "원";
                    break;
                case 2:
                    shapeName = "직사각형";
                    break;
                case 3:
                    shapeName = "삼각형";
                    break;
            }
            cout << shapeName << " ("; // 도형의 이름을 출력합니다.
            for (vector<double>::size_type i = 0; i < shape.lengths.size(); ++i) {
                cout << "길이 #" << (i + 1) << ": " << shape.lengths[i]; // 마지막 길이가 아닌 경우 쉼표를 출력합니다.
                if (i != shape.lengths.size() - 1) {
                    cout << ", ";
                }
            } // 둘레 길이를 출려합니다.
            cout << ") - 둘레 길이: " << shape.dulrae << endl;
        } //주석추가
    }
};

int main() {
    ShapeCal cal;
    cal.run();

    return 0;
}


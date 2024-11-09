#include "pch.h"
#include "CppUnitTest.h"
#include "../10.1.2/10.1.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1012
{
    TEST_CLASS(UnitTest1012)
    {
    public:

        TEST_METHOD(TestPercentHighGrades)
        {
            Student students[3] = {
                {"Katuna", I, ME, 4, 5, {}},
                {"Kachur", II, KN, 4, 4, {}},
                {"Nanana", III, MF, 3, 2, {}}
            };

            double expected_percentage = 66.67; 
            double actual_percentage = percent_high_grades(students, 3);
            Assert::AreEqual(expected_percentage, actual_percentage, 0.01, L"Percentage calculation is incorrect");
        }

        TEST_METHOD(TestCountProgGrades)
        {
            Student students[3] = {
                {"Ananas", I, KN, 4, 4, {}},
                {"Grusha", II, KN, 4, 4, {}},
                {"Kavun", III, MF, 3, 2, {}}
            };

            students[0].third_mark.mark_prog = 5;
            students[1].third_mark.mark_prog = 4;
            students[2].third_mark.mark_pedagogy = 3; 

            int count5, count4, count3;
            count_prog_grades(students, 3, count5, count4, count3);

            Assert::AreEqual(1, count5, L"Count of 5 grades is incorrect");
            Assert::AreEqual(1, count4, L"Count of 4 grades is incorrect");
            Assert::AreEqual(0, count3, L"Count of 3 grades is incorrect");
        }
    };
}

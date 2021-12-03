# Unit Testing Guide

## Adding new tests

Each component to test should have its own testing file. Start with making a testing fixture
This is a struct which is initialised and deleted before and after running each unit test
(although it can be a class instead of a struct since we don't need private members because we're only accessing components within the same testing module any encapsulation is unnecessary)

Then write your unit tests with the following format:
TEST_F(<FixtureName>, <UnitTestName>)


## Running tests
1. `./build.sh`
1. `./test.sh {args}`

To run a specific test, please add an arg like 
`"ExampleTests*"`, where ExampleTests is a name of a fixture.

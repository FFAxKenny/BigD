#include"../../util.h"

#include<CUnit/CUnit.h>
#include<CUnit/Basic.h>

#include "../../src/env/maze.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }


/**
 * test_uploadMaze - ensures that upload maze creates the correct object which
 * includes the actual map and wall mapping. (should also include display map).
 */
void test_uploadMaze(void) {
    FILE *mazeWallSol;
    char line[6];
    char wallSol[256][4];
    char mazeFilePath[] = "mazes/j1.maze.txt";
    char mazeSolFilePath[] = "mazes/j1.maze.txt.wall";
    Maze maze;
    uploadMaze(&maze,mazeFilePath);
    int i,j,row;

    mazeWallSol = fopen(mazeSolFilePath,"r"); 
    if(!mazeWallSol) {
        CU_FAIL("Could not find solution file");
    }

    for(i=0; fgets(line,6,mazeWallSol)!=NULL; i++) {
        wallSol[i][0]=line[0]-'0';
        wallSol[i][1]=line[1]-'0';
        wallSol[i][2]=line[2]-'0';
        wallSol[i][3]=line[3]-'0';
    }

    row = 0;
    for(i=0;i<16;i++) {
        for(j=0;j<16;j++) {
            CU_ASSERT_EQUAL(maze.actualMap[i][j].north,wallSol[row][0]);
            CU_ASSERT_EQUAL(maze.actualMap[i][j].east,wallSol[row][1]);
            CU_ASSERT_EQUAL(maze.actualMap[i][j].south,wallSol[row][2]);
            CU_ASSERT_EQUAL(maze.actualMap[i][j].west,wallSol[row][3]);
            row++;
        }
    }
}

void test_Stack(void) {
	Stack * stack;
	Coordinates * this=(Coordinates*)malloc(sizeof(Coordinates));
	Coordinates * that=(Coordinates*)malloc(sizeof(Coordinates));
	this->row = 5;
	this->col = 10;
	that->row = 10;
	that->col = 5;
	push(&stack,this);
	push(&stack,that);
	Coordinates * result;
	result = pop(&stack);
	CU_ASSERT_EQUAL(result->row,10);
	CU_ASSERT_EQUAL(result->col,5);
	result = pop(&stack);
	CU_ASSERT_EQUAL(result->row,5);
	CU_ASSERT_EQUAL(result->col,10);
}

int main( void ) {
    CU_pSuite pSuite = NULL;

    // initialize the CUnit test registry
    if( CUE_SUCCESS != CU_initialize_registry() ) return CU_get_error();

    // add a suite to the registry
    pSuite = CU_add_suite("maze_test_suite", init_suite, clean_suite);
    if( pSuite == NULL ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // add the tests to the suite
    if( CU_add_test(pSuite, "test_uploadMaze", test_uploadMaze)==NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

/*    
      //Run all tests using the automated interface
      CU_automated_run_tests();
      CU_list_tests_to_file();
      */
/*
      //Run all tests using the console interface
      CU_console_run_tests();
 */ 
    // Clean up registry and return
    CU_cleanup_registry();
    return CU_get_error();
}

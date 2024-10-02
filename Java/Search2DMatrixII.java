public class Search2DMatrixII {
    // Method to search for a target element in a 2D matrix
 public boolean searchMatrix(int[][] matrix, int target) {
        // If the matrix is empty, return false
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) return false;

        // Initialize the search boundaries
        int row = 0, col = matrix[0].length - 1;
        
        // Continue searching until the boundaries meet
        while (row < matrix.length && col >= 0) {
            // If the target is found, return true
            if (matrix[row][col] == target) return true;
            // If the target is less than the current element, move left
            else if (matrix[row][col] < target) row++;
            // If the target is greater than the current element, move up
            else col--;
        }
        // If the target is not found, return false
        return false;
    }

    public static void main(String[] args) {
        Search2DMatrixII solution = new Search2DMatrixII();
        int[][] matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
        int target = 3;
        boolean result = solution.searchMatrix(matrix, target);
        System.out.println("Is " + target + " in the matrix? " + result);
    }
}

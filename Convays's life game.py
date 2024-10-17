import pygame
import numpy as np

# Initialize the game window size and colors
WINDOW_SIZE = (800, 800)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRID_COLOR = (50, 50, 50)

# Set the size of the grid and the cells
CELL_SIZE = 10
GRID_WIDTH = WINDOW_SIZE[0] // CELL_SIZE
GRID_HEIGHT = WINDOW_SIZE[1] // CELL_SIZE

# Function to initialize the grid with random live and dead cells
def initialize_grid(randomize=True):
    if randomize:
        return np.random.randint(2, size=(GRID_WIDTH, GRID_HEIGHT))
    else:
        return np.zeros((GRID_WIDTH, GRID_HEIGHT))

# Function to draw the grid
def draw_grid(screen, grid):
    for x in range(GRID_WIDTH):
        for y in range(GRID_HEIGHT):
            rect = pygame.Rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE)
            if grid[x, y] == 1:
                pygame.draw.rect(screen, WHITE, rect)
            else:
                pygame.draw.rect(screen, BLACK, rect)
            pygame.draw.rect(screen, GRID_COLOR, rect, 1)

# Function to update the grid based on Conway's Game of Life rules
def update_grid(grid):
    new_grid = np.copy(grid)
    for x in range(GRID_WIDTH):
        for y in range(GRID_HEIGHT):
            # Get the number of live neighbors
            live_neighbors = np.sum(grid[max(0, x-1):min(GRID_WIDTH, x+2), max(0, y-1):min(GRID_HEIGHT, y+2)]) - grid[x, y]
            # Apply the Game of Life rules
            if grid[x, y] == 1:  # Live cell
                if live_neighbors < 2 or live_neighbors > 3:
                    new_grid[x, y] = 0  # Cell dies
            else:  # Dead cell
                if live_neighbors == 3:
                    new_grid[x, y] = 1  # Cell becomes alive
    return new_grid

# Main function to run the Game of Life simulation
def game_of_life():
    pygame.init()
    screen = pygame.display.set_mode(WINDOW_SIZE)
    pygame.display.set_caption("Conway's Game of Life")
    
    clock = pygame.time.Clock()

    # Initialize the grid
    grid = initialize_grid(randomize=True)

    running = True
    paused = False

    while running:
        screen.fill(BLACK)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    paused = not paused
                if event.key == pygame.K_r:
                    grid = initialize_grid(randomize=True)
                if event.key == pygame.K_c:
                    grid = initialize_grid(randomize=False)

        if not paused:
            grid = update_grid(grid)

        draw_grid(screen, grid)

        pygame.display.update()
        clock.tick(10)

    pygame.quit()

if __name__ == "__main__":
    game_of_life()

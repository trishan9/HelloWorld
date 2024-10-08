package HelloWorld.JavaProjects;
// Description: A simple task management tool to add, delete, and view tasks in a to-do list. Key Features:

// Add tasks
// Mark tasks as completed
// View all tasks (completed and pending)
import java.util.ArrayList;
import java.util.Scanner;

class Task {
    String description;
    boolean isCompleted;

    Task(String description) {
        this.description = description;
        this.isCompleted = false;
    }

    void complete() {
        isCompleted = true;
    }

    @Override
    public String toString() {
        return description + (isCompleted ? " [Completed]" : " [Pending]");
    }
}

public class ToDoListApplication {
    public static void main(String[] args) {
        ArrayList<Task> tasks = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Add Task\n2. Complete Task\n3. View Tasks\n4. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("Enter task description: ");
                    String description = scanner.nextLine();
                    tasks.add(new Task(description));
                    break;
                case 2:
                    System.out.print("Enter task number to complete: ");
                    int taskNumber = scanner.nextInt();
                    tasks.get(taskNumber - 1).complete();
                    break;
                case 3:
                    for (int i = 0; i < tasks.size(); i++) {
                        System.out.println((i + 1) + ". " + tasks.get(i));
                    }
                    break;
                case 4:
                    return;
            }
        }
    }
}


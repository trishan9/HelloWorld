use std::io;
use std::collections::VecDeque;

fn main() {
    let mut tasks: VecDeque<String> = VecDeque::new();

    loop {
        println!("--- To-Do List ---");
        println!("1. Add task");
        println!("2. View tasks");
        println!("3. Remove task");
        println!("4. Exit");

        let mut choice = String::new();
        io::stdin().read_line(&mut choice).expect("Failed to read input");

        match choice.trim() {
            "1" => add_task(&mut tasks),
            "2" => view_tasks(&tasks),
            "3" => remove_task(&mut tasks),
            "4" => {
                println!("Goodbye!");
                break;
            },
            _ => println!("Invalid choice, please select a valid option."),
        }
    }
}

fn add_task(tasks: &mut VecDeque<String>) {
    println!("Enter a new task:");
    let mut task = String::new();
    io::stdin().read_line(&mut task).expect("Failed to read input");
    
    tasks.push_back(task.trim().to_string());
    println!("Task added!");
}

fn view_tasks(tasks: &VecDeque<String>) {
    if tasks.is_empty() {
        println!("No tasks available.");
    } else {
        println!("Your tasks:");
        for (i, task) in tasks.iter().enumerate() {
            println!("{}. {}", i + 1, task);
        }
    }
}

fn remove_task(tasks: &mut VecDeque<String>) {
    if tasks.is_empty() {
        println!("No tasks to remove.");
        return;
    }
    
    println!("Enter the number of the task to remove:");
    let mut index_str = String::new();
    io::stdin().read_line(&mut index_str).expect("Failed to read input");

    match index_str.trim().parse::<usize>() {
        Ok(index) if index > 0 && index <= tasks.len() => {
            tasks.remove(index - 1);
            println!("Task removed!");
        },
        _ => println!("Invalid index."),
    }
}

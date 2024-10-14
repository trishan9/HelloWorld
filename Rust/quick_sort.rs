fn merge_sort(arr: &mut [i32]) {
    let len = arr.len();
    if len < 2 {
        return; 
    }

    let mid = len / 2;

    let mut left = arr[..mid].to_vec();
    let mut right = arr[mid..].to_vec();

    merge_sort(&mut left);
    merge_sort(&mut right);

    merge(arr, &left, &right);
}

fn merge(arr: &mut [i32], left: &[i32], right: &[i32]) {
    let (mut i, mut j, mut k) = (0, 0, 0);

    while i < left.len() && j < right.len() {
        if left[i] <= right[j] {
            arr[k] = left[i];
            i += 1;
        } else {
            arr[k] = right[j];
            j += 1;
        }
        k += 1;
    }
}

fn main(){
    let mut arr = [5, 3, 8, 6, 2, 7, 4, 1];
    println!("Before sorting: {:?}", arr);

    merge_sort(&mut arr);
    println!("After sorting: {:?}", arr);
}


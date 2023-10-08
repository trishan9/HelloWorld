class BubbleSort:
    def __init__(self, arr: list) -> None:
        self.arr = arr

    def sorting(self) -> list:
        for i in range(len(self.arr) - 1):
            for j in range(len(self.arr) - i - 1):
                if self.arr[j] > self.arr[j + 1]:
                    temp = self.arr[j]
                    self.arr[j] = self.arr[j + 1]
                    self.arr[j + 1] = temp

        return self.arr


print(BubbleSort([24, 23, 34, 2, 23, 53, 342]).sorting())

import matplotlib.pyplot as plt

def read_stats_file(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            stats_array = [list(map(int, line.split())) for line in lines]
            return stats_array
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def plot_line_plots(data):
    if data:
        # Transpose the data for easier plotting

        # Plotting each line
        for i, line_data in enumerate(data):
            plt.plot(line_data, label=f'Line {i+1}')
            plt.xlabel('Data Points')
            plt.ylabel('Values')
            plt.title('Line Plots of Data')
            plt.legend()
            plt.show()


    else:
        print("Cannot plot data. Check if the file was read successfully.")

# Example usage
file_path = "stats.txt"
data = read_stats_file(file_path)
plot_line_plots(data)
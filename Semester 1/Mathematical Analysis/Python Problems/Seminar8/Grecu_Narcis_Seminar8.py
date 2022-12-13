import random
from matplotlib import pyplot as plt


def generate_points(p_norm, number_of_points):
    """
    Generate points from the p-norm unit ball
    :param p_norm: p-norm
    :param number_of_points: number of points to generate
    :return: list of points
    """
    points = []

    while len(points) < number_of_points:
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        if abs(x)**p_norm + abs(y)**p_norm < 1:
            points.append((x, y))

    return points


def plot_points(points_first_norm, points_second_norm, points_third_norm, points_fourth_norm):
    """
    Plot points
    :param points_first_norm: points from the first norm
    :param points_second_norm: points from the second norm
    :param points_third_norm: points from the third norm
    :param points_fourth_norm: points from the fourth norm
    :return: None
    """

    x1 = [point[0] for point in points_first_norm]
    y1 = [point[1] for point in points_first_norm]

    x2 = [point[0] for point in points_second_norm]
    y2 = [point[1] for point in points_second_norm]

    x3 = [point[0] for point in points_third_norm]
    y3 = [point[1] for point in points_third_norm]

    x4 = [point[0] for point in points_fourth_norm]
    y4 = [point[1] for point in points_fourth_norm]

    figure, axis = plt.subplots(2, 2)

    axis[0, 0].scatter(x1, y1, color='red')
    axis[0, 0].set_title('Norm p = 1.25')

    axis[0, 1].scatter(x2, y2, color='green')
    axis[0, 1].set_title('Norm p = 1.5')

    axis[1, 0].scatter(x3, y3, color='blue')
    axis[1, 0].set_title('Norm p = 3.8')

    axis[1, 1].scatter(x4, y4, color='orange')
    axis[1, 1].set_title('Norm p = 2')

    figure.tight_layout()

    axis[0, 0].set_aspect('equal')
    axis[0, 1].set_aspect('equal')
    axis[1, 0].set_aspect('equal')
    axis[1, 1].set_aspect('equal')

    axis[0, 0].set_xticks([-2, -1, 0, 1, 2])
    axis[0, 0].set_yticks([-2, -1, 0, 1, 2])

    axis[0, 1].set_xticks([-2, -1, 0, 1, 2])
    axis[0, 1].set_yticks([-2, -1, 0, 1, 2])

    axis[1, 0].set_xticks([-2, -1, 0, 1, 2])
    axis[1, 0].set_yticks([-2, -1, 0, 1, 2])

    axis[1, 1].set_xticks([-2, -1, 0, 1, 2])
    axis[1, 1].set_yticks([-2, -1, 0, 1, 2])

    plt.show()


def main():
    norm1 = 1.25
    norm2 = 1.5
    norm3 = 3.8
    norm4 = 2

    number_of_points = 50000

    points_norm1 = generate_points(norm1, number_of_points)
    points_norm2 = generate_points(norm2, number_of_points)
    points_norm3 = generate_points(norm3, number_of_points)
    points_norm4 = generate_points(norm4, number_of_points)

    plot_points(points_norm1, points_norm2, points_norm3, points_norm4)


if __name__ == '__main__':
    main()

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_2
{
    public class SortingModule<T> where T:IComparable
    {
        public static List<T> Sort(List<T> listToSort, string sortingAlgorithm="merge", bool reverse=false)
        {
            switch (sortingAlgorithm)
            {
                case "merge":
                    MergeSort(listToSort, 0, listToSort.Count);
                    break;

                case "bubble":
                    BubbleSort(listToSort);
                    break;

                case "gnome":
                    GnomeSort(listToSort);
                    break;

                default:
                    // TODO: maybe throw an exception.
                    break;
            }

            if (reverse)
                ReverseList(listToSort);

            return listToSort;
        }

        private static void ReverseList(List<T> listToReverse)
        {
            int leftIndex = 0, rightIndex = listToReverse.Count - 1;

            while (leftIndex < rightIndex)
            {
                T item = listToReverse[leftIndex];
                listToReverse[leftIndex] = listToReverse[rightIndex];
                listToReverse[rightIndex] = item;

                leftIndex++;
                rightIndex--;
            }
        }

        public static void BubbleSort(List<T> listToSort)
        {
            bool isDone;

            do
            {
                isDone = true;

                for (int  i = 0; i < listToSort.Count - 1; i++)
                    if (listToSort[i].CompareTo(listToSort[i + 1]) > 0)
                    {
                        T auxCopy = listToSort[i];
                        listToSort[i] = listToSort[i + 1];
                        listToSort[i + 1] = auxCopy;

                        isDone = false;
                    }

            } while (!isDone);
        }

        private static void MergeLists(List<T> listToMerge, int startPosition, int endPosition) { 
            int middlePosition = (startPosition + endPosition) / 2;
            List<T> leftSubList = new List<T>(), rightSubList = new List<T>();

            for (int i = startPosition; i < middlePosition; i++)
                leftSubList.Add(listToMerge[i]);

            for (int i = middlePosition; i < endPosition; i++)
                rightSubList.Add(listToMerge[i]);

            int leftListIndex = 0, rightListIndex = 0;
            int listToMergeIndex = startPosition;

            while (leftListIndex < leftSubList.Count &&
                    rightListIndex < rightSubList.Count)
            {
                if (leftSubList[leftListIndex].CompareTo(rightSubList[rightListIndex]) < 0)
                    listToMerge[listToMergeIndex++] = leftSubList[leftListIndex++];

                else
                    listToMerge[listToMergeIndex++] = rightSubList[rightListIndex++];
            }

            while (leftListIndex < leftSubList.Count)
                listToMerge[listToMergeIndex++] = leftSubList[leftListIndex++];

            while (rightListIndex < rightSubList.Count)
                listToMerge[listToMergeIndex++] = rightSubList[rightListIndex++];
        }

        public static void MergeSort(List<T> listToSort, int startPosition, int endPosition)
        {
            if (startPosition >= endPosition)
                return;

            int middlePosition = (startPosition + endPosition) / 2;

            MergeSort(listToSort, startPosition, middlePosition);
            MergeSort(listToSort, middlePosition + 1, endPosition);

            MergeLists(listToSort, startPosition, endPosition);
        }

        public static void GnomeSort(List<T> listToSort)
        {
            int currentPosition = 0;

            while (currentPosition < listToSort.Count)
            {
                if (currentPosition == 0 ||
                    listToSort[currentPosition].CompareTo(listToSort[currentPosition - 1]) >= 0)
                    currentPosition += 1;

                else
                {
                    T auxCopy = listToSort[currentPosition];
                    listToSort[currentPosition] = listToSort[currentPosition - 1];
                    listToSort[currentPosition - 1] = auxCopy;

                    currentPosition -= 1;
                }
            }
        }
    }
}

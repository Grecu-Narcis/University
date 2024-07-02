import { useEffect, useState } from 'react';
import { getAllCars } from '../../services/Cars Service/CarsService';
import { CarDTO } from '../../types/CarDTO.types';
import { BarChart } from '@mui/x-charts';
import Loading from 'react-loading';

import './CarsChart.css';

export default function CarsChart() {
    const [isLoading, setIsLoading] = useState<boolean>(true);

    const [yearsMap, setYearsMap] = useState<Map<number, number>>(new Map());

    useEffect(() => {
        let computeYearsMap = new Map<number, number>();

        getAllCars().then((response) => {
            console.log('hello');
            console.log(response);
            response.forEach((currentCar: CarDTO) => {
                if (computeYearsMap.get(currentCar.year) === undefined) computeYearsMap.set(currentCar.year, 1);
                else computeYearsMap.set(currentCar.year, computeYearsMap.get(currentCar.year)! + 1);
            });

            computeYearsMap = new Map([...computeYearsMap.entries()].sort(([key1], [key2]) => key1 - key2));
            setYearsMap(computeYearsMap);
            setIsLoading(false);
        });
    }, []);

    if (isLoading) return <Loading type='spin' width={30} height={30} color='black' />;

    if (yearsMap.size === 0) return <div>No car in database!</div>;
    return (
        <div className='chart-wrapper' data-testid='chart-wrapper'>
            <BarChart
                xAxis={[
                    {
                        id: 'Manufacturing year',
                        data: [...yearsMap.keys()],
                        scaleType: 'band',
                    },
                ]}
                series={[
                    {
                        data: [...yearsMap.values()],
                    },
                ]}
                width={600}
                height={400}
            />
        </div>
    );
}

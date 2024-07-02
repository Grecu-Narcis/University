import { useEffect, useState } from 'react';
import './CarGallery.css';
import { Car } from '../../models/car';
import { getCarsPage, getTotalCarCount } from '../../services/Cars Service/CarsService';
import Loading from 'react-loading';
import InfiniteScroll from 'react-infinite-scroll-component';
import { CarCard } from '../Display Cars/CarCard';

export default function CarGallery() {
    const [cars, setCars] = useState<Car[]>([]);
    const [totalCount, setTotalCount] = useState<number>(0);
    const [page, setPage] = useState<number>(1);

    const pageSize = 30;

    const [isLoadingCars, setIsLoadingCars] = useState<boolean>(true);
    const [isLoadingTotalCount, setIsLoadingTotalCount] = useState<boolean>(true);

    const fetchCars = () => {
        getCarsPage(page, pageSize).then((response) => {
            setCars([...cars, ...response]);
            setPage(page + 1);
        });
    };

    useEffect(() => {
        getCarsPage(0, pageSize).then((response) => {
            setCars(response);
            setIsLoadingCars(false);
        });

        getTotalCarCount().then((response) => {
            setTotalCount(response);
            setIsLoadingTotalCount(false);
        });
    }, []);

    if (isLoadingCars || isLoadingTotalCount) return <Loading type='spin' width={'40px'} color='black' />;

    return (
        <InfiniteScroll
            data-testid='cars-infinite-scroll'
            next={fetchCars}
            hasMore={cars.length < totalCount}
            loader={<Loading type='spin' color='black' />}
            dataLength={cars.length}
            className='all-cars-scroll'
        >
            {cars.map((car) => (
                <CarCard key={car.getId()} givenCar={car} readOnly={false} />
            ))}
        </InfiniteScroll>
    );
}

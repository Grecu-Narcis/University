import { createContext, useEffect, useState } from 'react';
import { Car } from '../models/car';
import CompareCarsPopup from '../features/Compare Cars/Compare Cars Popup/CompareCarsPopup';

type CompareCarsContextProps = {
    cars: Car[];
    addCar: (carToAdd: Car) => void;
    clearCars: () => void;
};

export const CompareCarsContext = createContext<CompareCarsContextProps | null>(null);

export default function CompareCarsContextProvider({ children }: any) {
    const [cars, setCars] = useState<Car[]>([]);
    const addCar = (carToAdd: Car) => {
        if (cars.find((currentCar) => carToAdd.getId() === currentCar.getId())) return;
        setCars([...cars, carToAdd]);
    };

    const clearCars = () => setCars([]);

    useEffect(() => {}, [cars]);

    return (
        <CompareCarsContext.Provider
            value={{
                cars: cars,
                addCar: addCar,
                clearCars,
            }}
        >
            {cars.length > 0 && <CompareCarsPopup />}
            {children}
        </CompareCarsContext.Provider>
    );
}

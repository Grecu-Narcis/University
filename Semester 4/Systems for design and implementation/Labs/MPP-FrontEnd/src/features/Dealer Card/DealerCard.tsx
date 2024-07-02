import { DealerCardProps } from '../../types/DealerCardProps.types';
import { Button } from '../../shared/components/button/Button';

import './DealerCard.css';
import { useNavigate } from 'react-router-dom';

export function DealerCard({ dealer }: DealerCardProps) {
    const navigate = useNavigate();

    const handleViewCarsClick = () => {
        navigate('/cars/' + dealer.id);
    };

    return (
        <div className='dealer-card'>
            <div className='dealer-presentation'>
                <img src='/assets/default-dealer.jpg' className='dealer-profile-image' />
                <div className='dealer-info'>
                    <div className='dealer-name'>{dealer.firstName + ' ' + dealer.lastName}</div>
                    <div className='dealer-email'>{dealer.email}</div>
                </div>
            </div>

            <Button type='button' buttonMessage='View cars' className='view-cars-button' onClick={handleViewCarsClick} />
        </div>
    );
}

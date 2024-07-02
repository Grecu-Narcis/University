// ShareButton.js
import { TwitterShareButton, TwitterIcon, WhatsappShareButton, WhatsappIcon } from 'react-share';
import { Car } from '../../models/car';

type ShareButtonProps = {
    car: Car;
};

const ShareButton = ({ car }: ShareButtonProps) => {
    const url = `http://localhost:3000/viewCar/${car.getId()}`;
    const title = `${car.getBrand()} ${car.getModel()} for sale`;

    return (
        <div
            style={{
                display: 'flex',
            }}
        >
            <WhatsappShareButton
                url={url}
                title={title}
                style={{
                    marginRight: '1rem',
                }}
            >
                <WhatsappIcon size={32} round />
            </WhatsappShareButton>

            <TwitterShareButton url={url} title={title}>
                <TwitterIcon size={32} round />
            </TwitterShareButton>
        </div>
    );
};

export default ShareButton;

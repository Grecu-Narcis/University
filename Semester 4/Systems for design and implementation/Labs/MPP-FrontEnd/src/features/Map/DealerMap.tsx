import { Map, Marker } from '@vis.gl/react-google-maps';

import './DealerMap.css';

type DealerMapProps = {
    latitude: number | undefined;
    longitude: number | undefined;
    setLatitude?: (newLatitude: number) => void;
    setLongitude?: (newLongitude: number) => void;
};

export default function DealerMap({ latitude, longitude, setLatitude, setLongitude }: DealerMapProps) {
    return (
        <Map
            className='map'
            defaultZoom={13}
            defaultCenter={{ lat: latitude ? latitude : 47.74, lng: longitude ? longitude : 26.65 }}
            onClick={(ev) => {
                if (ev.detail.latLng) {
                    if (setLatitude && setLongitude) {
                        setLatitude(ev.detail.latLng.lat);
                        setLongitude(ev.detail.latLng.lng);
                    }
                }
            }}
        >
            {latitude && longitude && <Marker position={{ lat: latitude, lng: longitude }}></Marker>}
        </Map>
    );
}

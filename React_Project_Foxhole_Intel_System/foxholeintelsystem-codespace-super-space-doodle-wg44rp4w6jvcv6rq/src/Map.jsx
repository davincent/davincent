import React, { useRef, useEffect, useState } from 'react';
import L from 'leaflet';
import 'leaflet/dist/leaflet.css';
import { v4 as uuidv4 } from 'uuid';

function MapComponent() {
    const mapRef = useRef(null);
    const [worlds, setWorlds] = useState({});
    const [contextMenu, setContextMenu] = useState({ visible: false, x: 0, y: 0, latlng: null, worldId: null });

    // Set Map Extents
    const southWest = L.latLng(-256, 0);
    const northEast = L.latLng(0, 256);
    const bounds = L.latLngBounds(southWest, northEast);

    // World Extent constants (in centimeters)
    const WORLD_EXTENT_MIN = { x: -109199.999997, y: -94499.99999580907 };
    const WORLD_EXTENT_MAX = { x: 109199.999997, y: 94499.99999580907 };
    const WORLD_EXTENT_WIDTH = WORLD_EXTENT_MAX.x - WORLD_EXTENT_MIN.x;
    const WORLD_EXTENT_HEIGHT = WORLD_EXTENT_MAX.y - WORLD_EXTENT_MIN.y;

    // Function to calculate the number of tiles needed to cover the bounds at a given zoom level
    const calculateTileRange = (bounds, zoom) => {
        const tileSize = 256; // Assuming your tiles are 256x256 pixels
        const zoomFactor = Math.pow(2, zoom);

        // Get the pixel coordinates of the bounds at the current zoom level
        const nwPixel = mapRef.current.project(bounds.getNorthWest(), zoom).floor();
        const sePixel = mapRef.current.project(bounds.getSouthEast(), zoom).ceil();

        // Calculate the tile coordinates
        const minTileX = Math.floor(nwPixel.x / tileSize);
        const maxTileX = Math.floor(sePixel.x / tileSize);
        const minTileY = Math.floor(nwPixel.y / tileSize);
        const maxTileY = Math.floor(sePixel.y / tileSize);

        return { minX: minTileX, maxX: maxTileX, minY: minTileY, maxY: maxTileY };
    };

    useEffect(() => {
        // Initialize the map with Simple CRS
        mapRef.current = L.map('map-container', {
            crs: L.CRS.Simple,
            minZoom: 1,
            maxZoom: 6,
            bounds: bounds, // Set initial bounds
            maxBounds: bounds, // Prevent panning/zooming outside these bounds
        }).setView([0, 0], 3);

        // Add a tile layer (adjust bounds based on your overall map)
        L.tileLayer('/Tiles/{z}/{z}_{x}_{y}.png', {
            attribution: 'Foxhole',
            noWrap: true,
            bounds: bounds,
            tileSize: 256, // Ensure tileSize is specified if needed
        }).addTo(mapRef.current);

        // Set Markers at corners of the map (for visual reference)
        L.marker(northEast).bindPopup('Top Right').addTo(mapRef.current);
        L.marker(southWest).bindPopup('Bottom Left').addTo(mapRef.current);

        // Function to calculate the vertices of a world (hex) based on a center point
        const getWorldPolygonPoints = (center, displayRadius) => {
            const points = [];
            for (let i = 0; i < 6; i++) {
                const angle = (Math.PI / 3) * i;
                const x = center.x + displayRadius * Math.cos(angle);
                const y = center.y + displayRadius * Math.sin(angle);
                points.push([y, x]); // [lat, lng] in Simple CRS => [y, x]
            }
            return points;
        };

        // Function to add a world (hex) to the map
        const addWorld = (center, id) => {
            const displayRadius = 18.25; // Adjust for the visual size of the hex on the map
            const points = getWorldPolygonPoints(center, displayRadius);
            const polygon = L.polygon(points, {
                color: 'orange',
                weight: 2,
                opacity: 1,
                fillColor: 'clear',
                fillOpacity: 0.3,
                id: id,
            });

            polygon.on('contextmenu', (e) => {
                e.originalEvent.preventDefault();
                setContextMenu({
                    visible: true,
                    x: e.originalEvent.clientX,
                    y: e.originalEvent.clientY,
                    latlng: e.latlng,
                    worldId: polygon.options.id,
                });
            });

            polygon.addTo(mapRef.current);
            return polygon;
        };

        // Example of adding some initial worlds
        const initialWorldCenters = [
            { x: 237.75, y: -159.75 }
        ];

        const hexHeight = 31.7; // Vertical distance between hex centers
        const hexSide = hexHeight*.5;
        const hexWidth = Math.sqrt(3)*hexSide; // Horizontal distance between hex centers
        const numCols = 9; // Number of columns

        // Add hexes in a grid pattern
        var i = 0;

        for (let j = 1; j < 3; j++) {
            const yOffset = j * hexHeight;
            const center = { x: initialWorldCenters[i].x, y: yOffset };
            initialWorldCenters.push(center);
        }

        i += 1;

        for (let j = 0; j < 4; j++) {
            const yOffset = j * hexHeight;
            const xOffset = i * hexWidth;
            const center = { x: xOffset, y: yOffset};
            initialWorldCenters.push(center);
        }





        const initialWorlds = {};
        initialWorldCenters.forEach(center => {
            const id = uuidv4();
            const world = addWorld(center, id);
            initialWorlds[id] = { center, layer: world };
        });
        setWorlds(initialWorlds);

        return () => {
            if (mapRef.current) {
                mapRef.current.remove();
            }
        };
    }, []);

    const handleContextMenuAction = (action) => {
        setContextMenu({ ...contextMenu, visible: false, worldId: null });
        if (contextMenu.worldId) {
            const selectedWorld = worlds[contextMenu.worldId];
            if (selectedWorld) {
                console.log(`Action "${action}" on world ID: ${contextMenu.worldId} at coordinates:`, contextMenu.latlng);
                // Implement actions based on the selected world and action
            }
        }
    };

    return (
        <div style={{ position: 'relative', height: '100vh', width: '100%' }}>
            <div id="map-container" style={{ height: '100%', width: '100%' }}></div>

            {contextMenu.visible && (
                <div
                    style={{
                        position: 'absolute',
                        left: contextMenu.x,
                        top: contextMenu.y,
                        backgroundColor: 'white',
                        border: '1px solid black',
                        padding: '5px',
                        zIndex: 1000,
                    }}
                >
                    <h3>World Actions</h3>
                    <button onClick={() => handleContextMenuAction('details')}>View Details</button><br />
                    {/* Add more world-specific actions */}
                </div>
            )}
        </div>
    );
}

export default MapComponent;
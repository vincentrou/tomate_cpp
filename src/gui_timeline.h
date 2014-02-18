
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QGraphicsItemGroup>

#include "dataset.h"
#include "gui_widgets/EditCropDialog.h"


class CropTimeRepresentation: public QGraphicsItemGroup
{
public:
    CropTimeRepresentation(Crop& crop, QDate date0 = QDate(), QWidget* parent = NULL);
    QGraphicsRectItem* create_rect(QDate start_date, QDate end_date, bool planned=false);
    void delete_me();
    Crop* get_pcrop();
    //void show(QPoint point, Crop* p_crop);
private:
    Crop& crop;
    QDate date0;
};


class MonthsRepresentation: public QGraphicsItemGroup
{
public:
    MonthsRepresentation(QDate date_start, QDate date_end, QWidget* parent=NULL);
private:
};


class WholeTimeScene: public QGraphicsScene
{
  Q_OBJECT

public:
    WholeTimeScene(Dataset& dataset, QWidget* parent=NULL);
    void draw_scene();
    void clear_crops();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    EditCropDialog* get_ecd() { return edit_crop_dialog; };

public slots:
    void redraw();
    void previous_year();
    void next_year();

signals:
    void current_date_changed(QDate date);

private:
    Dataset& dataset;
    EditCropDialog* edit_crop_dialog;
    QMenu* context_menu;
    QDate date;
    vector<CropTimeRepresentation*> crop_reprs;
    
    void add_year_buttons();
    void draw_date_line(QDate date);
};

class WholeTimeSceneView: public QGraphicsView
{
    Q_OBJECT

public:
    WholeTimeSceneView(Dataset& dataset, QWidget* parent=NULL);
    void update_draw();
    void update_rect();
    WholeTimeScene* get_scene() { return _scene; };

private:
    WholeTimeScene* _scene;
};

class TimelineWindow: public QWidget
{
    Q_OBJECT

public:
    TimelineWindow(Dataset& dataset, QWidget* parent=NULL);
    WholeTimeSceneView* get_view() { return &view; };
    
private slots:
    void update();

private:
    WholeTimeSceneView view;
};